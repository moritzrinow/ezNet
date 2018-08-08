// This code was mostly taken from https://github.com/etodd/lasercrabs.

#pragma once

/* Debug assert code */

#ifdef _WIN32
#define bn_debug_break() __debugbreak()
#elif defined(__ORBIS__)
#define bn_debug_break() __builtin_trap()
#elif defined(__clang__)
#define bn_debug_break() __builtin_debugtrap()
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__APPLE__)
#include <signal.h>
#define bn_debug_break() raise(SIGTRAP)
#elif defined(__GNUC__)
#define bn_debug_break __builtin_trap()
#else
#define bn_debug_break ((void)0)
#endif

#define bn_debug(fmt, ...) fprintf(stderr, "%s:%d: " fmt "\n", __func__, __LINE__, __VA_ARGS__)

#define check(expression) \
          if(!(expression)) \
            bn_debug_break();

#define assert(expression) check(expression)