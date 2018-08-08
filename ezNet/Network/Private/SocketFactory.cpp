// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#include "../Public/SocketFactory.h"
#include "../Public/Socket.h"

EZNET_BEGIN

ISocket * SocketFactory::CreateSocket()
{
  ISocket* socket = new Socket();
  return socket;
}

ISocket * SocketFactory::CreateSocket(bool blocking)
{
  ISocket* socket = new Socket(blocking);
  return socket;
}

void SocketFactory::DestroySocket(ISocket* socket)
{
  delete socket;
}

EZNET_END