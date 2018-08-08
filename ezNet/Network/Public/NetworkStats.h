// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Common/Public/Defines.h"
#include "Common/Public/Types.h"

EZNET_BEGIN

struct SendingStats;
struct ReceivingStats;
struct NetworkStats;


struct SendingStats {

  SendingStats()
    : BytesPerSecond(0),
      PacketsPerSecond(0)
  {
  }

  int64 BytesPerSecond;
  int64 PacketsPerSecond; // Maybe messages per second
};

struct ReceivingStats {

  ReceivingStats()
    : BytesPerSecond(0),
      PacketsPerSecond(0)
  {
  }

  int64 BytesPerSecond;
  int64 PacketsPerSecond; // Maybe messages per second
};

struct NetworkStats {

  NetworkStats()
    : OutStats(),
      InStats(),
      TotalRequests(0),
      RequestsPerSecond(0)
  {
  }
  
  int64 TotalRequests;
  int32 RequestsPerSecond;
  SendingStats OutStats;
  ReceivingStats InStats;
};

EZNET_END