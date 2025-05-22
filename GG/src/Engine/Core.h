#pragma once

#if defined(__APPLE__)
  #define GG_API __attribute__((visibility("default")))
#endif

#define GG_ASSERT(x, ...) { if(!(x)) { GG_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#define GG_CORE_ASSERT(x, ...) { if(!(x)) { GG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }

// 生成只有第 x 位为 1 的掩码
#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
