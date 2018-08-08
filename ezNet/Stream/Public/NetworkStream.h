// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "IStream.h"
#include "Network/Public/ISocket.h"

EZNET_BEGIN

class NetworkStream;

/*
* Represents a stream of bytes that is transported over the network.
*/
class NetworkStream : public IStream {

public:

  NetworkStream(ISocket* socket);
  ~NetworkStream();

  /*
  * Get the underlying ISocket object.
  */
  ISocket* Socket();

  /*
  * Not supported!(Always false)
  */
  bool EndOfStream() override; // Always false

  /*
  * Not supported!(Returns -1)
  */
  int32 Length() override; // Nothing

  /*
  * Not supported!(Returns -1)
  */
  int32 GetPosition() override; // Nothing

  /*
  * Not supported!(Does not set anything)
  */
  void SetPosition(int32 position) override;

  /*
  * Closes the underlying socket connection.
  */
  void Close(int32 waitMs) override;

  /*
  * Not supported!(Does nothing)
  */
  void CopyTo(IStream * destination) override;

  /*
  * Supported by default.
  */
  int32 Read(byte * buffer, int32 offset, int32 count) override;

  /*
  * Supported by default.
  */
  int32 ReadByte() override;

  /*
  * Supported by default.
  */
  void Write(byte * buffer, int32 offset, int32 count) override;

  /*
  * Supported by default.
  */
  void WriteByte(byte value) override;

private:

  ISocket* m_socket;
};

EZNET_END