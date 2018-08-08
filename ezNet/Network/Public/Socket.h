// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "ISocket.h"

EZNET_BEGIN

class Socket;

/*
* The standart implementation of the ISocket interface.
*/
class Socket : public ISocket {

public:

  /******************************/
  /* Constructors / Destructors */
  /******************************/

  Socket(bool blocking = true);
  Socket(NativeSocket socket);
  ~Socket();

  /***********/
  /* Control */
  /***********/

  ISocket* Accept() override;
  bool Close() override;
  bool Bind(NativeSockAddrIn* addr, int32 addrSize) override;
  bool Connect(NativeSockAddrIn* addr, int32 addrSize) override;
  bool Listen(int32 backlog) override;

  /******/
  /* IO */
  /******/

  int32 Receive(char* buffer, int32 length, int32 flags) override;
  int32 Receive(byte* buffer, int32 length, int32 flags) override;
  int32 Send(const char* buffer, int32 length, int32 flags) override;
  int32 Send(byte* buffer, int32 length, int32 flags) override;

  /***********/
  /* Get/set */
  /***********/

  NativeSocket NativeHandle() override;
  void SetAddress(NativeSockAddrIn* addr) override;
  void SetBlocking(bool shouldBlock) override;
  bool IsBlocking() override;

private:

  /*****************/
  /* Blocking mode */
  /*****************/

  ISocket* Accept_blocking();
  int32 Receive_blocking(char* buffer, int32 length, int32 flags);
  int32 Receive_blocking(byte* buffer, int32 length, int32 flags);
  int32 Send_blocking(const char* buffer, int32 length, int32 flags);
  int32 Send_blocking(byte* buffer, int32 length, int32 flags);

  /********************/
  /* Non-blockin mode */
  /********************/

  ISocket* Accept_non_blocking();
  int32 Receive_non_blocking(char* buffer, int32 length, int32 flags);
  int32 Receive_non_blocking(byte* buffer, int32 length, int32 flags);
  int32 Send_non_blocking(const char* buffer, int32 length, int32 flags);
  int32 Send_non_blocking(byte* buffer, int32 length, int32 flags);

  /********/
  /* Data */
  /********/

  bool m_blocking;
  NativeSocket m_socket;
  NativeSockAddrIn m_addr;
};

EZNET_END
