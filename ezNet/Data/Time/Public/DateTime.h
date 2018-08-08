// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Common/Public/Defines.h"
#include "Common/Public/Types.h"
#include "TimeSpan.h"

EZNET_BEGIN

struct DateTime;

typedef struct tm NativeTime;
typedef time_t NativeRawTime;

#define YEAR_OFFSET 1900

struct DateTime {

  DateTime();
  
  /* Data */

  int32 Second;
  int32 Minute;
  int32 Hour;
  int32 Day;
  int32 Month;
  int32 Year;
  int32 WeekDay;
  int32 YearDay;

  /* Operators */

  bool operator ==(DateTime time); // Works
  bool operator !=(DateTime time); // Works

  bool operator <(DateTime time); // Works fine I guess
  bool operator >(DateTime time); // Works fine I guess

  DateTime operator +(TimeSpan span); // Does not work
  DateTime operator -(TimeSpan span); // Does not work
  TimeSpan operator -(DateTime time); // Works fine I guess

  /* Methods */

  NativeTime ToNativeTime();
  int64 TotalTicks();
};

enum class EWeekDay {
  Monday = 0,
  Tuesday = 1,
  Wednesday = 2,
  Thursday = 3,
  Friday = 4,
  Saturday = 5,
  Sunday = 6,
  Unknown = 7
};

EZNET_END