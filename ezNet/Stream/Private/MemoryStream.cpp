#include "../Public/MemoryStream.h"

EZNET_BEGIN

MemoryStream::MemoryStream()
  : m_array(), m_position(0)
{
}

MemoryStream::MemoryStream(int32 capacity)
  : m_array(capacity), m_position(0)
{
}

MemoryStream::MemoryStream(TDynArray<byte> buffer)
  : m_array(buffer), m_position(0)
{
}

MemoryStream::MemoryStream(byte * buffer, int32 count)
  : m_array(buffer, count), m_position(0)
{
}

MemoryStream::~MemoryStream()
{
}

bool MemoryStream::EndOfStream()
{
  return m_position == m_array.Length();
}

int32 MemoryStream::Length()
{
  return m_array.Length();
}

int32 MemoryStream::GetPosition()
{
  return m_position;
}

void MemoryStream::SetPosition(int32 position)
{
  assert(position >= 0 && position <= Length());
  m_position = position;
}

void MemoryStream::Close(int32 waitMs)
{
}

void MemoryStream::CopyTo(IStream * destination)
{
  destination->Write(m_array.GetArray(), 0, Length());
}

int32 MemoryStream::Read(byte * buffer, int32 offset, int32 count)
{
  int32 bytesLeft = Length() - m_position;
  if (bytesLeft == 0) {
    return -1;
  }
  if (bytesLeft > count) {
    bytesLeft = count;
  }

  byte* buffer_ptr = m_array.GetArray();
  Memcpy((void*)&buffer[offset], &buffer_ptr[m_position], bytesLeft);
  m_position += bytesLeft;
}

int32 MemoryStream::ReadByte()
{
  int32 bytesLeft = Length() - m_position;
  if (bytesLeft == 0) {
    return -1;
  }

  return (int32)m_array[m_position++];
}

void MemoryStream::Write(byte * buffer, int32 offset, int32 count)
{
  int32 bytesLeft = Length() - m_position;
  if (bytesLeft < count) {
    m_array.Resize(Length() + (count - bytesLeft));
  }

  byte* buffer_ptr = m_array.GetArray();
  Memcpy((void*)&buffer_ptr[m_position], (void*)&buffer[offset], count);
  m_position += count;
}

void MemoryStream::WriteByte(byte value)
{
  Write(&value, 0, 1);
}

byte * MemoryStream::ToNativeArray()
{
  byte* bufferCopy = (byte*)Malloc(Length());
  
  byte* buffer_ptr = m_array.GetArray();
  Memcpy((void*)bufferCopy, (void*)buffer_ptr, Length());

  return bufferCopy;
}

EZNET_END
