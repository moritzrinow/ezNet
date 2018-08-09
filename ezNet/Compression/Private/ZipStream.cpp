// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#include "../Public/ZipStream.h"
#include "Common/Public/Assert.h"
#include "ThirdParty/FastLZ/fastlz.h"

EZNET_BEGIN

ZipStream::ZipStream(IStream * stream, ECompressionMode mode, int32 originalSize)
  : m_mode(mode), m_readStream(), m_decompressedWell(false), m_originalSize(originalSize)
{
  if (stream->Length() == -1) {
    assert(false);
  }

  m_baseStream = stream;

  switch (m_mode) {
  case ECompressionMode::Compress:
    m_level = ECompressionLevel::Fast;
    break;

  case ECompressionMode::Decompress:
    m_level = ECompressionLevel::None;
    m_decompressedWell = DecompressToInternalBuffer();
    break;

  default:
    assert(false);
  }
}

ZipStream::ZipStream(IStream * stream, ECompressionLevel level)
  : m_level(level), m_readStream(), m_decompressedWell(false), m_originalSize(0)
{
  if (stream->Length() == -1) {
    assert(false);
  }

  m_baseStream = stream;

  switch (m_level) {
  case ECompressionLevel::Fast:
  case ECompressionLevel::Strong:
    m_mode = ECompressionMode::Compress;
    break;

  case ECompressionLevel::None:
    m_mode = ECompressionMode::Decompress;
    m_decompressedWell = DecompressToInternalBuffer();
    break;

  default:
    assert(false);
  }
}

ZipStream::~ZipStream()
{
}

ECompressionMode ZipStream::Mode()
{
  return m_mode;
}

ECompressionLevel ZipStream::Level()
{
  return m_level;
}

bool ZipStream::DecompressedWell()
{
  return m_decompressedWell;
}

IStream * ZipStream::BaseStream()
{
  return m_baseStream;
}

bool ZipStream::EndOfStream()
{
  return false;
}

int32 ZipStream::Length()
{
  return -1;
}

int32 ZipStream::GetPosition()
{
  return -1;
}

void ZipStream::SetPosition(int32 position)
{
  // Does nothing
}

void ZipStream::Close(int32 waitMs)
{
  m_baseStream->Close(waitMs);
}

void ZipStream::CopyTo(IStream * destination)
{
  if (m_mode == ECompressionMode::Compress) {
    m_baseStream->CopyTo(destination);
    return;
  }

  if (m_mode == ECompressionMode::Decompress) {
    m_readStream.CopyTo(destination);
    return;
  }
}

int32 ZipStream::Read(byte * buffer, int32 offset, int32 count)
{
  if (m_mode == ECompressionMode::Compress) {
    return -1;
  }

  return m_readStream.Read(buffer, offset, count);
}

int32 ZipStream::ReadByte()
{
  if (m_mode == ECompressionMode::Compress) {
    return -1;
  }

  return m_readStream.ReadByte();
}

void ZipStream::Write(byte * buffer, int32 offset, int32 count)
{
  if (m_mode == ECompressionMode::Decompress) {
    return;
  }

  if (count < ZIP_MIN_IN_BUFFER_SIZE) {
    return;
  }

  byte* inBuffer = (byte*)Malloc(count);
  Memcpy(inBuffer, &buffer[offset], count); // Copy input buffer
  byte* outBuffer = nullptr;
  int32 outBufferLength = 0;

  if (count <= 62) { // We can take min size for out buffer
    outBuffer = (byte*)Malloc(ZIP_MIN_OUT_BUFFER_SIZE);
    outBufferLength = ZIP_MIN_OUT_BUFFER_SIZE;
  }
  else { // We have to take more than min size for out buffer
    outBufferLength = ((double)count * ZIP_MIN_OUT_BUFFER_COMPARED_TO_IN + 1);
    outBuffer = (byte*)Malloc(outBufferLength);
  }

  int32 result = fastlz_compress_level((int32)m_level, inBuffer, count, outBuffer); // Call compress lib
  if (result > count) { // Error
    bn_debug_break();
    Free(inBuffer);
    Free(outBuffer);
    return;
  }

  m_baseStream->Write(outBuffer, 0, result); // Write compressed bytes to underlying stream

  Free(inBuffer);
  Free(outBuffer);
}

void ZipStream::WriteByte(byte value)
{
  // Does nothing
}

bool ZipStream::DecompressToInternalBuffer()
{
  if (m_baseStream->Length() < ZIP_MIN_IN_BUFFER_SIZE) {
    return false;
  }

  MemoryStream inStream(m_baseStream->Length());
  m_baseStream->CopyTo(&inStream);
  byte* inbuffer = inStream.ToNativeArray();
  int32 inBufferLength = inStream.Length();

  int32 outBufferLength = m_originalSize + 10;

  if (outBufferLength < ZIP_MIN_OUT_BUFFER_SIZE) {
    outBufferLength = ZIP_MIN_OUT_BUFFER_SIZE;
  }

  byte* outBuffer = (byte*)Malloc(outBufferLength);

  int32 result = fastlz_decompress(inbuffer, inBufferLength, outBuffer, outBufferLength);
  if (result <= 0) {
    bn_debug_break();
    Free(inbuffer);
    Free(outBuffer);
    return false;
  }

  m_readStream.Write(outBuffer, 0, result);

  Free(inbuffer);
  Free(outBuffer);
  return true;
}

EZNET_END