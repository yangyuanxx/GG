#pragma once

#if defined(__APPLE__)
  #define GG_API __attribute__((visibility("default")))
#endif

#define BIT(x) (1 << x)