// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Common/Public/Defines.h"
#include "Common/Public/Types.h"

EZNET_BEGIN

struct TimeSpan;

#define MILLISECONDS_PER_SECOND 1000
#define MILLISECONDS_PER_MINUTE 60000
#define MILLISECONDS_PER_HOUR 3600000
#define MILLISECONDS_PER_DAY 86400000
#define MILLISECONDS_PER_WEEK 604800000
#define MILLISECONDS_PER_MONTH 2629800000
#define MILLISECONDS_PER_YEAR 31557600000

#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_DAY 86400
#define SECONDS_PER_WEEK 604800
#define SECONDS_PER_MONTH 2629800
#define SECONDS_PER_YEAR 31557600

#define MINUTES_PER_HOUR 60
#define MINUTES_PER_DAY 1440
#define MINUTES_PER_WEEK 10080
#define MINUTES_PER_MONTH 43830
#define MINUTES_PER_YEAR 525960

#define HOURS_PER_DAY 24
#define HOURS_PER_WEEK 168
#define HOURS_PER_MONTH_AVERAGE 730.5
#define HOURS_PER_MONTH_LOW 720
#define HOURS_PER_MONTH_HIGH 744
#define HOURS_PER_YEAR 8766

#define DAYS_PER_WEEK 7
#define DAYS_PER_MONTH_AVERAGE 30.4375
#define DAYS_PER_MONTH_LOW 30
#define DAYS_PER_MONTH_HIGH 31
#define DAYS_PER_YEAR_AVERAGE 365.25
#define DAYS_PER_YEAR_LOW 365
#define DAYS_PER_YEAR_HIGH 366

#define WEEKS_PER_MONTH 4
#define WEEKS_PER_YEAR 52.17857

#define MONTHS_PER_YEAR 12

#define TICKS_PER_MILLISECOND 10000LL
#define TICKS_PER_SECOND 10000000LL
#define TICKS_PER_MINUTE 600000000LL
#define TICKS_PER_HOUR 36000000000LL
#define TICKS_PER_DAY 864000000000LL
#define TICKS_PER_MONTH (TICKS_PER_DAY * DAYS_PER_MONTH_AVERAGE)
#define TICKS_PER_YEAR (TICKS_PER_MONTH * MONTHS_PER_YEAR)

/*
* Represents a time span.
*/
struct TimeSpan {

  TimeSpan();
  TimeSpan(int64 ticks);
  TimeSpan(int32 hours, int32 minutes, int32 seconds);
  TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds);
  TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds, int32 milliseconds);

  /* Data */

  int32 Milliseconds;
  int32 Seconds;
  int32 Minutes;
  int32 Hours;
  int32 Days;

  /* Methods */

  int64 TotalTicks();
  double TotalMilliseconds();
  double TotalSeconds();
  double TotalMinutes();
  double TotalHours();
  double TotalDays();
  double TotalMonths();
  double TotalYears();

  /* Operators */

  bool operator ==(TimeSpan span);
  bool operator !=(TimeSpan span);

  bool operator <(TimeSpan span);
  bool operator >(TimeSpan span);

  bool operator <=(TimeSpan span);
  bool operator >=(TimeSpan span);

  TimeSpan operator +(TimeSpan span);
  TimeSpan operator -(TimeSpan span);

  void operator +=(TimeSpan span);
  void operator -=(TimeSpan span);
};

EZNET_END