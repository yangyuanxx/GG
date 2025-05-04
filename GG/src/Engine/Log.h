#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace GG {
  class GG_API Log {
    public:
      static void Init();
      inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
      inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
      static std::shared_ptr<spdlog::logger> s_CoreLogger;
      static std::shared_ptr<spdlog::logger> s_ClientLogger;
  };
}

// Core log macros
#define GG_CORE_TRACE(...)    ::GG::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GG_CORE_INFO(...)     ::GG::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GG_CORE_WARN(...)     ::GG::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GG_CORE_ERROR(...)    ::GG::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GG_CORE_CRITIAL(...)    ::GG::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GG_TRACE(...)         ::GG::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GG_INFO(...)          ::GG::Log::GetClientLogger()->info(__VA_ARGS__)
#define GG_WARN(...)          ::GG::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GG_ERROR(...)         ::GG::Log::GetClientLogger()->error(__VA_ARGS__)
#define GG_CRITICAL(...)      ::GG::Log::GetClientLogger()->critical(__VA_ARGS__)