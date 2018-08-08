// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#include "../Public/TimeSpan.h"
#include "Common/Public/Defines.h"

EZNET_BEGIN

TimeSpan::TimeSpan()
  : Milliseconds(0),
    Seconds(0),
    Minutes(0),
    Hours(0),
    Days(0)
{
}

TimeSpan::TimeSpan(int64 ticks)
{
  int64 rest = ticks;

  int32 days = (ticks / TICKS_PER_DAY); // Get full days from all ticks
  rest = (rest - (days * TICKS_PER_DAY)); // Get the remainding ticks

  int32 hours = (rest / TICKS_PER_HOUR); // Get full hours from remainding ticks
  rest = (rest - (hours * TICKS_PER_HOUR)); // Get the remainding ticks

  int32 minutes = (rest / TICKS_PER_MINUTE);
  rest = (rest - (minutes * TICKS_PER_MINUTE));

  int32 seconds = (rest / TICKS_PER_SECOND);
  rest = (rest - (seconds * TICKS_PER_SECOND));

  int32 milliseconds = (rest / TICKS_PER_MILLISECOND);
  rest = (rest - (milliseconds * TICKS_PER_MILLISECOND));

  
  Milliseconds = milliseconds;
  Seconds = seconds;
  Minutes = minutes;
  Hours = hours;
  Days = days;
}

TimeSpan::TimeSpan(int32 hours, int32 minutes, int32 seconds)
{
  int64 ticks = 0;

  ticks += (hours * TICKS_PER_HOUR);
  ticks += (minutes * TICKS_PER_MINUTE);
  ticks += (seconds * TICKS_PER_SECOND);

  TimeSpan span(ticks);
  *this = span;
}

TimeSpan::TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds)
{
  int64 ticks = 0;

  ticks += (days * TICKS_PER_DAY);
  ticks += (hours * TICKS_PER_HOUR);
  ticks += (minutes * TICKS_PER_MINUTE);
  ticks += (seconds * TICKS_PER_SECOND);

  TimeSpan span(ticks);
  *this = span;
}

TimeSpan::TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds, int32 milliseconds)
{
  int64 ticks = 0;

  ticks += (days * TICKS_PER_DAY);
  ticks += (hours * TICKS_PER_HOUR);
  ticks += (minutes * TICKS_PER_MINUTE);
  ticks += (seconds * TICKS_PER_SECOND);
  ticks += (milliseconds * TICKS_PER_MILLISECOND);

  TimeSpan span(ticks);
  *this = span;
}

double TimeSpan::TotalMinutes()
{
  double totalMinutes = 0.0;

  totalMinutes += (scast<double>(Days) * scast<double>(MINUTES_PER_DAY));
  totalMinutes += (scast<double>(Hours) * scast<double>(MINUTES_PER_HOUR));
  totalMinutes += Minutes;
  totalMinutes += (scast<double>(Seconds) / scast<double>(SECONDS_PER_MINUTE));
  totalMinutes += (scast<double>(Milliseconds) / scast<double>(MILLISECONDS_PER_MINUTE));

  return totalMinutes;
}

double TimeSpan::TotalHours()
{
  double totalHours = 0.0;

  totalHours += (scast<double>(Days) * scast<double>(HOURS_PER_DAY));
  totalHours += Hours;
  totalHours += (scast<double>(Minutes) / scast<double>(MINUTES_PER_HOUR));
  totalHours += (scast<double>(Seconds) / scast<double>(SECONDS_PER_HOUR));
  totalHours += (scast<double>(Milliseconds) / scast<double>(MILLISECONDS_PER_HOUR));

  return totalHours;
}

double TimeSpan::TotalDays()
{
  double totalDays = 0.0;

  totalDays += Days;
  totalDays += (scast<double>(Hours) / scast<double>(HOURS_PER_DAY));
  totalDays += (scast<double>(Minutes) / scast<double>(MINUTES_PER_DAY));
  totalDays += (scast<double>(Seconds) / scast<double>(SECONDS_PER_DAY));
  totalDays += (scast<double>(Milliseconds) / scast<double>(MILLISECONDS_PER_DAY));

  return totalDays;
}

int64 TimeSpan::TotalTicks()
{
  int64 ticks = 0;
  ticks += (Milliseconds * TICKS_PER_MILLISECOND);
  ticks += (Seconds * TICKS_PER_SECOND);
  ticks += (Minutes * TICKS_PER_MINUTE);
  ticks += (Hours * TICKS_PER_HOUR);
  ticks += (Days * TICKS_PER_DAY);

  return ticks;
}

double TimeSpan::TotalMonths()
{
  double totalMinutes = TotalMinutes();
  double totalMonths = (totalMinutes / MINUTES_PER_MONTH);
  return totalMonths;
}

double TimeSpan::TotalYears()
{
  double totalMonths = TotalMonths();
  double totalYears = (totalMonths / MONTHS_PER_YEAR);
  return totalYears;
}

bool TimeSpan::operator ==(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();
  return ticks1 == ticks2;
}

bool TimeSpan::operator !=(TimeSpan span)
{
  return !(*this == span);
}

bool TimeSpan::operator <(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();
  return ticks1 < ticks2;
}

bool TimeSpan::operator >(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();
  return ticks1 > ticks2;
}

bool TimeSpan::operator <=(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();
  return ticks1 <= ticks2;
}

bool TimeSpan::operator >=(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();
  return ticks1 >= ticks2;
}

TimeSpan TimeSpan::operator +(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();

  TimeSpan result(ticks1 + ticks2);
  return result;
}

TimeSpan TimeSpan::operator -(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();

  TimeSpan result(ticks1 - ticks2);
  return result;
}

void TimeSpan::operator +=(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();

  TimeSpan result(ticks1 + ticks2);
  *this = result;
}

void TimeSpan::operator -=(TimeSpan span)
{
  int64 ticks1 = TotalTicks();
  int64 ticks2 = span.TotalTicks();

  TimeSpan result(ticks1 - ticks2);
  *this = result;
}

double TimeSpan::TotalMilliseconds()
{
  double totalMilliseconds = 0.0;

  totalMilliseconds += (scast<double>(Days) * scast<double>(MILLISECONDS_PER_DAY));
  totalMilliseconds += (scast<double>(Hours) * scast<double>(MILLISECONDS_PER_HOUR));
  totalMilliseconds += (scast<double>(Minutes) * scast<double>(MILLISECONDS_PER_MINUTE));
  totalMilliseconds += (scast<double>(Seconds) * scast<double>(MILLISECONDS_PER_SECOND));
  totalMilliseconds += Milliseconds;

  return totalMilliseconds;
}

double TimeSpan::TotalSeconds()
{
  double totalSeconds = 0.0;

  totalSeconds += (scast<double>(Days) * scast<double>(SECONDS_PER_DAY));
  totalSeconds += (scast<double>(Hours) * scast<double>(SECONDS_PER_HOUR));
  totalSeconds += (scast<double>(Minutes) * scast<double>(SECONDS_PER_MINUTE));
  totalSeconds += Seconds;
  totalSeconds += (scast<double>(Milliseconds) / scast<double>(MILLISECONDS_PER_SECOND));

  return totalSeconds;
}

EZNET_END
