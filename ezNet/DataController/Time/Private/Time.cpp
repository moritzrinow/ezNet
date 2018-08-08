// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#include <time.h>
#include "../Public/Time.h"
#include "Common/Public/Defines.h"

EZNET_BEGIN

DateTime Time::Now()
{
  time_t raw;
  tm info;

  time(&raw);
  localtime_s(&info, &raw);
  info.tm_year += YEAR_OFFSET;

  DateTime dateTime;
  dateTime.Second = info.tm_sec;
  dateTime.Minute = info.tm_min;
  dateTime.Hour = info.tm_hour;
  dateTime.Day = info.tm_mday;
  dateTime.Month = info.tm_mon;
  dateTime.Year = info.tm_year;
  dateTime.WeekDay = info.tm_wday;
  dateTime.YearDay = info.tm_yday;

  return dateTime;
}

EWeekDay Time::GetWeekDay(const DateTime& time)
{
  EWeekDay day = scast<EWeekDay>(time.WeekDay);
  return day;
}

EWeekDay Time::GetCurrentWeekDay()
{
  return Time::GetWeekDay(Time::Now());
}

bool Time::IsWeekendNow()
{
  bool isWeekend = false;

  EWeekDay today = Time::GetCurrentWeekDay();
  switch (today) {
  case EWeekDay::Saturday:
  case EWeekDay::Sunday:
    isWeekend = true;
    break;

  default:
    break;
  }

  return IsWeekend;
}

bool Time::IsWeekend(EWeekDay day)
{
  return false;
}

EZNET_END