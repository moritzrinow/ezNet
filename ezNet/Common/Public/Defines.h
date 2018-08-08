// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include <thread>

/******************/
/* Casting macros */
/******************/

#define scast static_cast
#define rcast reinterpret_cast
#define dcast dynamic_cast

/****************/
/* Thread sleep */
/****************/

#define Sleeps(s) std::this_thread::sleep_for(std::chrono::seconds(s));
#define Sleepms(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms));

/********/
/* Math */
/********/

#define negate(number) (-1 * (number))

/**********/
/* Memory */
/**********/

/* Allocates a memory block on the heap */
#define Malloc malloc

/* Allocates a memory block on the heap and zero's the bytes */
#define Calloc calloc

/* Reallocates (size)bytes at a given address */
#define Realloc realloc

/* Deallocates a memory block on the heap */
#define Free free

/* Set's (size)bytes the the given address to a value */
#define Memset memset

/* Copies (size)bytes to a given address */
#define Memcpy memcpy

/* Moves (size)bytes from a source address to a new address */
#define Memmove memmove

/* Zero's (size)bytes at the given address */
#define ZeroMem(addr,size) memset(addr, 0, size)

/*************/
/* Namespace */
/*************/

#define EZNET_BEGIN namespace eznet {
#define EZNET_END }