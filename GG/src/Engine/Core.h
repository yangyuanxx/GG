#pragma once

#if defined(__APPLE__)
  #define GG_API __attribute__((visibility("default")))
#endif

#define GG_ASSERT(x, ...) { if(!(x)) { GG_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#define GG_CORE_ASSERT(x, ...) { if(!(x)) { GG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }

#define BIT(x) (1 << x)