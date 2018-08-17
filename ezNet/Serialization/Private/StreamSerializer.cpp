// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#include "../Public/StreamSerializer.h"

EZNET_BEGIN

void StreamSerializer::WriteInt8(IStream * stream, int8 inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

void StreamSerializer::WriteInt16(IStream * stream, int16 inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

void StreamSerializer::WriteInt32(IStream * stream, int32 inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

void StreamSerializer::WriteInt64(IStream * stream, int64 inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

bool StreamSerializer::ReadInt8(IStream * stream, int8 * outValue)
{
  return (stream->Read((byte*)outValue, 0, sizeof(int8)) == sizeof(int8));
}

bool StreamSerializer::ReadInt16(IStream * stream, int16 * outValue)
{
  return (stream->Read((byte*)outValue, 0, sizeof(int16)) == sizeof(int16));
}

bool StreamSerializer::ReadInt32(IStream * stream, int32 * outValue)
{
  return (stream->Read((byte*)outValue, 0, sizeof(int32)) == sizeof(int32));
}

bool StreamSerializer::ReadInt64(IStream * stream, int64 * outValue)
{
  return (stream->Read((byte*)outValue, 0, sizeof(int64)) == sizeof(int64));
}

void StreamSerializer::WriteUInt8(IStream * stream, uint8 inValue)
{
  stream->Write(&inValue, 0, sizeof(inValue));
}

void StreamSerializer::WriteUInt16(IStream * stream, uint16 inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

void StreamSerializer::WriteUInt32(IStream * stream, uint32 inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

void StreamSerializer::WriteUInt64(IStream * stream, uint64 inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

void StreamSerializer::WriteFloat(IStream * stream, float inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

void StreamSerializer::WriteDouble(IStream * stream, double inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

bool StreamSerializer::ReadFloat(IStream * stream, float * outValue)
{
  return (stream->Read((byte*)outValue, 0, sizeof(float)) == sizeof(float));
}

bool StreamSerializer::ReadDouble(IStream * stream, double * outValue)
{
  return (stream->Read((byte*)outValue, 0, sizeof(double)) == sizeof(double));
}

void StreamSerializer::WriteBool(IStream * stream, bool inValue)
{
  stream->Write((byte*)&inValue, 0, sizeof(inValue));
}

bool StreamSerializer::ReadBool(IStream * stream, bool * outValue)
{
  return (stream->Read((byte*)outValue, 0, sizeof(bool)) == sizeof(bool));
}

void StreamSerializer::WriteString(IStream * stream, const char * inValue)
{
  stream->Write((byte*)inValue, 0, strlen(inValue) + 1);
}

void StreamSerializer::WriteString(IStream * stream, char * inValue, int32 size)
{
  stream->Write((byte*)inValue, 0, size);
}

bool StreamSerializer::ReadString(IStream * stream, char * outValue, int32 size)
{
  if (size <= 0) {
    return false;
  }

  *outValue = '\0';

  for (int i = 0; i < size; i++) {
    int32 current = stream->ReadByte();
    if (current < 0) { // No bytes left
      break;
    }

    char value = (char)current;
    outValue[i] = value;
    if (value == '\0') { // End of string
      return true;
    }
  }

  return false; // There were not enough bytes in the stream to build a valid string
}

EZNET_END
