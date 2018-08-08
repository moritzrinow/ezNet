// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#include "../Public/DateTime.h"
#include "Common/Public/Defines.h"

EZNET_BEGIN

TimeSpan DateToTimeSpan(DateTime time);
DateTime TimeSpanToDate(TimeSpan span);

DateTime::DateTime()
  : Second(0),
    Minute(0),
    Hour(0),
    Day(0),
    Month(0),
    Year(0),
    WeekDay(scast<int32>(EWeekDay::Unknown)),
    YearDay(0)
{
}

bool DateTime::operator ==(DateTime time)
{
  return Second == time.Second &&
    Minute == time.Minute &&
    Hour == time.Hour &&
    Day == time.Day &&
    Month == time.Month &&
    Year == time.Year &&
    WeekDay == time.WeekDay &&
    YearDay == time.YearDay;
}

bool DateTime::operator !=(DateTime time)
{
  return !(*this == time);
}

bool DateTime::operator <(DateTime time)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = time.TotalTicks();

  return ticks1 < ticks2;
}

bool DateTime::operator >(DateTime time)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = time.TotalTicks();

  return ticks1 > ticks2;
}

DateTime DateTime::operator +(TimeSpan span)
{
  TimeSpan span1 = DateToTimeSpan(*this);
  TimeSpan result = span1 + span;

  return TimeSpanToDate(result);
}

DateTime DateTime::operator -(TimeSpan span)
{
  TimeSpan span1 = DateToTimeSpan(*this);
  TimeSpan result = span1 - span;

  return TimeSpanToDate(result);
}

TimeSpan DateTime::operator -(DateTime time)
{
  NativeTime time1 = ToNativeTime();
  NativeTime other = time.ToNativeTime();

  double diffSeconds = difftime(mktime(&time1), mktime(&other));
  TimeSpan span(0, 0, diffSeconds);
  return span;
}

NativeTime DateTime::ToNativeTime()
{
  NativeTime nativeTime;
  nativeTime.tm_sec = Second;
  nativeTime.tm_min = Minute;
  nativeTime.tm_hour = Hour;
  nativeTime.tm_mday = Day;
  nativeTime.tm_mon = Month;
  nativeTime.tm_year = Year - YEAR_OFFSET; // Make sure to bring the year into native form
  nativeTime.tm_wday = WeekDay;
  nativeTime.tm_yday = YearDay;
  
  return nativeTime;
}

int64 DateTime::TotalTicks()
{
  int64 ticks = 0;
  ticks += (scast<int64>(Year) * TICKS_PER_YEAR);
  ticks += (scast<int64>(YearDay) * TICKS_PER_DAY);
  ticks += (scast<int64>(Hour) * TICKS_PER_HOUR);
  ticks += (scast<int64>(Minute) * TICKS_PER_MINUTE);
  ticks += (scast<int64>(Second) * TICKS_PER_SECOND);

  return ticks;
}

TimeSpan DateToTimeSpan(DateTime time)
{
  int64 ticks = time.TotalTicks();
  TimeSpan span(ticks);
  
  return span;
}

DateTime TimeSpanToDate(TimeSpan span)
{
#define years_left(seconds) (seconds / scast<double>(SECONDS_PER_YEAR))
#define months_left(seconds) (seconds / scast<double>(SECONDS_PER_MONTH))
#define days_left(seconds) (seconds / scast<double>(SECONDS_PER_DAY))
#define hours_left(seconds) (seconds / scast<double>(SECONDS_PER_HOUR))
#define minutes_left(seconds) (seconds / scast<double>(SECONDS_PER_MINUTE))

  int64 ticks = span.TotalTicks();
  TimeSpan validSpan(ticks);
  
  double secondsLeft = validSpan.TotalSeconds();

  int32 tempYear = years_left(secondsLeft);
  secondsLeft -= (scast<double>(tempYear) * SECONDS_PER_YEAR);

  int32 tempYearDay = days_left(secondsLeft);

  int32 tempMonth = months_left(secondsLeft);
  secondsLeft -= (scast<double>(tempMonth) * SECONDS_PER_MONTH);

  int32 tempDay = days_left(secondsLeft);
  secondsLeft -= (scast<double>(tempDay) * SECONDS_PER_DAY);

  int32 tempHour = hours_left(secondsLeft);
  secondsLeft -= (scast<double>(tempHour) * SECONDS_PER_HOUR);

  int32 tempMinute = minutes_left(secondsLeft);
  secondsLeft -= (scast<double>(tempMinute) * SECONDS_PER_MINUTE);

  int32 tempSecond = secondsLeft;

  DateTime time;
  time.Year = tempYear;
  time.Month = tempMonth;
  time.Day = tempDay;
  time.Hour = tempHour;
  time.Minute = tempMinute;
  time.Second = tempSecond;
  time.YearDay = tempYearDay;
  time.WeekDay = scast<int32>(EWeekDay::Unknown);

  return time;
}

EZNET_END