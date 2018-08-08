// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Common/Public/Defines.h"
#include "Common/Public/Types.h"

EZNET_BEGIN

/*
* Interface to work with streams of bytes.
* Please be aware that some methods might not be supported by some deriving classes.
*/
class IStream {

public:
  
  /**********************/
  /* Virtual destructor */
  /**********************/

  virtual ~IStream() {}

  /***********/
  /* Get/set */
  /***********/

  /*
  * This should return true, if the end of the stream was reached or false, if not.
  */
  virtual bool EndOfStream() = 0;

  /*
  * This should return the actual number of bytes in this current stream.
  */
  virtual int32 Length() = 0;

  /*
  * This should return the current stream's position.
  */
  virtual int32 GetPosition() = 0;

  /*
  * This should set the current stream's position.
  */
  virtual void SetPosition(int32 position) = 0;

  /******/
  /* IO */
  /******/

  /*
  * This should clean up all resources and make further reading / writing impossible after a specific waiting time.
  */
  virtual void Close(int32 waitMs) = 0;

  /*
  * This should copy the whole content of the current stream to a destination stream
  * at it's current position.
  */
  virtual void CopyTo(IStream* destination) = 0;

  /*
  * This should copy (count)bytes from the current stream at the current position into a byte array.
  * Should return the actual number of bytes read or -1 if nothing was read or an error occured.
  * @offset: The offset of @buffer.
  */
  virtual int32 Read(byte* buffer, int32 offset, int32 count) = 0;

  /*
  * This should read the next byte from the current stream at the current position and return
  * it's value as an int32 or -1 if it fails or nothing could be read.
  */
  virtual int32 ReadByte() = 0;

  /*
  * This should write (count)bytes from the input buffer to the current stream at the current
  * position.
  * @offset: The offset of @buffer.
  */
  virtual void Write(byte* buffer, int32 offset, int32 count) = 0;

  /*
  * This should write one input byte to the current stream at the current position.
  */
  virtual void WriteByte(byte value) = 0;
};

EZNET_END