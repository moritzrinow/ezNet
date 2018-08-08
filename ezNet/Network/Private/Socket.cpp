// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#include "Common/Public/Assert.h"
#include "Common/Public/Types.h"
#include "Common/Public/Defines.h"
#include "../Public/Socket.h"

EZNET_BEGIN

Socket::Socket(bool blocking)
  : m_blocking(blocking)
{
  m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  assert(m_socket != INVALID_SOCKET);

  SetBlocking(m_blocking);
}

Socket::Socket(NativeSocket socket)
  : m_socket(socket)
{
  assert(m_socket != INVALID_SOCKET);
}

Socket::~Socket()
{
  Close();
}

ISocket* Socket::Accept()
{
  if (m_blocking) {
    return Accept_blocking();
  }
  else {
    return Accept_non_blocking();
  }
}

bool Socket::Close()
{
  bool closed = (closesocket(m_socket) == 0);
  return closed;
}

bool Socket::Bind(NativeSockAddrIn* addr, int32 addrSize)
{
  bool bound = (bind(m_socket, (NativeSockAddr*)addr, addrSize) == 0);
  assert(bound);
  return bound;
}

bool Socket::Connect(NativeSockAddrIn* addr, int32 addrSize)
{
  bool connected = (connect(m_socket, (NativeSockAddr*)addr, addrSize) == 0);
  assert(connected);
  return connected;
}

bool Socket::Listen(int32 backlog)
{
  bool listening = (listen(m_socket, backlog) == 0);
  assert(listening)
  return listening;
}

int32 Socket::Receive(char* buffer, int32 length, int32 flags)
{
  if (m_blocking) {
    return Receive_blocking(buffer, length, flags);
  }
  else {
    return Receive_non_blocking(buffer, length, flags);
  }
}

int32 Socket::Receive(byte * buffer, int32 length, int32 flags)
{
  return Receive(rcast<char*>(buffer), length, flags);
}

int32 Socket::Send(const char* buffer, int32 length, int32 flags)
{
  if (m_blocking) {
    return Send_blocking(buffer, length, flags);
  }
  else {
    return Send_non_blocking(buffer, length, flags);
  }
}

int32 Socket::Send(byte * buffer, int32 length, int32 flags)
{
  return Send(rcast<const char*>(buffer), length, flags);
}

NativeSocket Socket::NativeHandle()
{
  return m_socket;
}

void Socket::SetAddress(NativeSockAddrIn * addr)
{
  m_addr = *addr;
}

void Socket::SetBlocking(bool shouldBlock)
{
  ULONG mode = shouldBlock ? 0 : 1;
  bool success = ioctlsocket(m_socket, FIONBIO, &mode) == 0;
  assert(success);
  m_blocking = shouldBlock;
}

bool Socket::IsBlocking()
{
  return m_blocking;
}

ISocket * Socket::Accept_blocking()
{
  int32 size = sizeof(NativeSockAddrIn);
  NativeSockAddrIn addr;
  ZeroMem(&addr, size);
  NativeSocket newSock = accept(m_socket, (NativeSockAddr*)&addr, &size);

  if (newSock == INVALID_SOCKET) {
    int32 error = WSAGetLastError();
    bn_debug_break();
  }

  Socket* sock = new Socket(newSock);
  sock->SetAddress(&addr);
  return sock;
}

int32 Socket::Receive_blocking(char * buffer, int32 length, int32 flags)
{
  int32 received = recv(m_socket, buffer, length, flags);
  bool closed = received == 0;
  bool error = received < 0;
  return received;
}

int32 Socket::Receive_blocking(byte * buffer, int32 length, int32 flags)
{
  return Receive_blocking(rcast<char*>(buffer), length, flags);
}

int32 Socket::Send_blocking(const char * buffer, int32 length, int32 flags)
{
  int32 sent = send(m_socket, buffer, length, flags);
  bool sentWell = sent != SOCKET_ERROR;
  return sent;
}

int32 Socket::Send_blocking(byte * buffer, int32 length, int32 flags)
{
  return Send_blocking(rcast<const char*>(buffer), length, flags);
}

ISocket * Socket::Accept_non_blocking()
{
  int32 size = sizeof(NativeSockAddrIn);
  NativeSockAddrIn addr;
  ZeroMem(&addr, size);
  NativeSocket newSock = accept(m_socket, (NativeSockAddr*)&addr, &size);

  if (newSock == INVALID_SOCKET || newSock == -1) {
    return nullptr;
  }

  Socket* sock = new Socket(newSock);
  sock->SetAddress(&addr);
  return sock;
}

int32 Socket::Receive_non_blocking(char * buffer, int32 length, int32 flags)
{
  return recv(m_socket, buffer, length, flags);
}

int32 Socket::Receive_non_blocking(byte * buffer, int32 length, int32 flags)
{
  return Receive_non_blocking(rcast<char*>(buffer), length, flags);
}

int32 Socket::Send_non_blocking(const char * buffer, int32 length, int32 flags)
{
  return send(m_socket, buffer, length, flags);
}

int32 Socket::Send_non_blocking(byte * buffer, int32 length, int32 flags)
{
  return Send_non_blocking(rcast<const char*>(buffer), length, flags);
}

EZNET_END