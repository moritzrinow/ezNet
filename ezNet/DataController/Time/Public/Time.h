// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Data/Time/Public/DateTime.h"
#include "Data/Time/Public/TimeSpan.h"

EZNET_BEGIN

class Time;

/*
* Class with static methods to work with time.
*/
class Time {
public:
  
  static DateTime Now();
  static EWeekDay GetWeekDay(const DateTime& time);
  static EWeekDay GetCurrentWeekDay();
  static bool IsWeekendNow();
  static bool IsWeekend(EWeekDay day);
};

EZNET_END