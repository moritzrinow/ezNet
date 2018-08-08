// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "NetworkModuleBaseIncludes.h"
#include "Common/Public/Defines.h"
#include "Common/Public/Types.h"

EZNET_BEGIN

class ISocket;

/*
* Interface to work with sockets.
*/
class ISocket {

public:

  /**********************/
  /* Virtual destructor */
  /**********************/

  virtual ~ISocket(){}

  /***********/
  /* Control */
  /***********/

  virtual ISocket* Accept() = 0;
  virtual bool Close() = 0;
  virtual bool Bind(NativeSockAddrIn* addr, int32 addrSize) = 0; // We need the address size, because there is sockaddr and sockaddr_in
  virtual bool Connect(NativeSockAddrIn* addr, int32 addrSize) = 0;
  virtual bool Listen(int32 backlog) = 0;

  /******/
  /* IO */
  /******/

  virtual int32 Receive(char* buffer, int32 length, int32 flags) = 0;
  virtual int32 Receive(byte* buffer, int32 length, int32 flags) = 0;
  virtual int32 Send(const char* buffer, int32 length, int32 flags) = 0;
  virtual int32 Send(byte* buffer, int32 length, int32 flags) = 0;

  /***********/
  /* Get/set */
  /***********/

  virtual NativeSocket NativeHandle() = 0;
  virtual void SetAddress(NativeSockAddrIn* addr) = 0;
  virtual void SetBlocking(bool shouldBlock) = 0;
  virtual bool IsBlocking() = 0;
};

EZNET_END