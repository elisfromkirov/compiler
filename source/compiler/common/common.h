#pragma once

#include <cassert>

#define ASSERT(expression) assert(expression)

#if __clang__ || __GNUC__
#define UNREACHABLE() __builtin_unreachable()
#else
#define UNREACHABLE()
#endif