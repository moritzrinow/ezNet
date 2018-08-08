#include "../Public/NetworkStream.h"

EZNET_BEGIN

NetworkStream::NetworkStream(ISocket* socket)
  : m_socket(socket)
{
}

NetworkStream::~NetworkStream()
{
  delete m_socket;
}

ISocket * NetworkStream::Socket()
{
  return m_socket;
}

bool NetworkStream::EndOfStream()
{
  return false;
}

int32 NetworkStream::Length()
{
  return -1;
}

int32 NetworkStream::GetPosition()
{
  return -1;
}

void NetworkStream::SetPosition(int32 position)
{
  // Does nothing
}

void NetworkStream::Close(int32 waitMs)
{
  Sleepms(waitMs);
  m_socket->Close();
}

void NetworkStream::CopyTo(IStream * destination)
{
  // Does nothing
}

int32 NetworkStream::Read(byte * buffer, int32 offset, int32 count)
{
  return m_socket->Receive(buffer, count, 0);
}

int32 NetworkStream::ReadByte()
{
  byte buffer = -1;
  int32 result = m_socket->Receive(&buffer, 1, 0);
  return buffer;
}

void NetworkStream::Write(byte * buffer, int32 offset, int32 count)
{
  m_socket->Send(buffer, count, 0);
}

void NetworkStream::WriteByte(byte value)
{
  m_socket->Send(&value, 1, 0);
}

EZNET_END