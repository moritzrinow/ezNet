// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Stream/Public/MemoryStream.h"

EZNET_BEGIN

class StreamSerializer;

/*
* Class with static methods to serialize primitive data into byte streams.
*/
class StreamSerializer {

public:

  /*******************/
  /* Signed integers */
  /*******************/

  static void WriteInt8(IStream* stream, int8 inValue);
  static void WriteInt16(IStream* stream, int16 inValue);
  static void WriteInt32(IStream* stream, int32 inValue);
  static void WriteInt64(IStream* stream, int64 inValue);

  static bool ReadInt8(IStream* stream, int8* outValue);
  static bool ReadInt16(IStream* stream, int16* outValue);
  static bool ReadInt32(IStream* stream, int32* outValue);
  static bool ReadInt64(IStream* stream, int64* outValue);

  /*********************/
  /* Unsigned integers */
  /*********************/

  static void WriteUInt8(IStream* stream, uint8 inValue);
  static void WriteUInt16(IStream* stream, uint16 inValue);
  static void WriteUInt32(IStream* stream, uint32 inValue);
  static void WriteUInt64(IStream* stream, uint64 inValue);

  /******************/
  /* Floating point */
  /******************/

  static void WriteFloat(IStream* stream, float inValue);
  static void WriteDouble(IStream* stream, double inValue);

  static bool ReadFloat(IStream* stream, float* outValue);
  static bool ReadDouble(IStream* stream, double* outValue);

  /***********/
  /* Boolean */
  /***********/

  static void WriteBool(IStream* stream, bool inValue);

  static bool ReadBool(IStream* stream, bool* outValue);

  /**********/
  /* String */
  /**********/

  static void WriteString(IStream* stream, const char* inValue);
  static void WriteString(IStream* stream, char* inValue, int32 size);

  static bool ReadString(IStream* stream, char* outValue, int32 size);
};

EZNET_END