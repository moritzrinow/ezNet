// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Data/Container/Public/TArray.h"
#include "IStream.h"

EZNET_BEGIN

class MemoryStream;

/*
* Represents a stream of bytes in memory.
* For further documentation look into the IStream class.
*/
class MemoryStream : public IStream {

public:

  /******************************/
  /* Constructors / destructors */
  /******************************/

  MemoryStream();
  MemoryStream(int32 capacity);
  MemoryStream(TDynArray<byte> buffer);
  MemoryStream(byte* buffer, int32 count);
  ~MemoryStream();

  /***********/
  /* Get/set */
  /***********/

  /*
  * Supported by default.
  */
  bool EndOfStream() override;

  /*
  * Supported by default.
  */
  int32 Length() override;

  /*
  * Supported by default.
  */
  int32 GetPosition() override;

  /*
  * Supported by default.
  */
  void SetPosition(int32 position) override;

  /******/
  /* IO */
  /******/

  /*
  * Not supported! (Does nothing)
  */
  void Close(int32 waitMs) override;

  /*
  * Supported by default.
  */
  void CopyTo(IStream* destination) override;

  /*
  * Supported by default.
  */
  int32 Read(byte* buffer, int32 offset, int32 count) override;

  /*
  * Supported by default.
  */
  int32 ReadByte() override;

  /*
  * Supported by default.
  */
  void Write(byte* buffer, int32 offset, int32 count) override;

  /*
  * Supported by default.
  */
  void WriteByte(byte value) override;

  /*
  * Copies the whole content of the stream to a byte array on the heap.
  * Remember to clean up the memory if no longer needed.
  */
  byte* ToNativeArray();

private:

  /********/
  /* Data */
  /********/

  int32 m_position;
  TDynArray<byte> m_array;
};

EZNET_END