workspace "GG"
  architecture "arm64"
  configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "GG/vendor/GLFW"
include "GG/vendor/Glad"
include "GG/vendor/imgui"

project "GG"
  location "GG"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"
  
  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  -- precompiled header，加速编译
  pchheader "ggpch.h"
  pchsource "Engine/src/ggpch.cpp"

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/vendor/glm/glm/**.hpp",
    "%{prj.name}/vendor/glm/glm/**.inl",
  }

  -- 只包含一级目录，不包含子目录
  includedirs {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
    "%{prj.name}/vendor/GLFW/include",
    "%{prj.name}/vendor/Glad/include",
    "%{prj.name}/vendor/imgui",
    "%{prj.name}/vendor/glm"
  }

  defines {
    "GLFW_INCLUDE_NONE"
  }

  filter "configurations:Debug"
    defines "GG_DEBUG"
    runtime "Debug"
    symbols "on"
    
  filter "configurations:Release"
    defines "GG_RELEASE"
    runtime "Release"
    optimize "on"
    
  filter "configurations:Dist"
    defines "GG_DIST"
    runtime "Release"
    optimize "on"

project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  includedirs {
    "GG/vendor/spdlog/include",
    "GG/src",
    "GG/vendor",
    "GG/vendor/glm"
  }

  links {
    "GG",
    "GLFW",
    "Glad",
    "ImGui",
    "OpenGL.framework",
    "Cocoa.framework",
    "IOKit.framework",
    "CoreFoundation.framework",
    "QuartzCore.framework",
    "CoreVideo.framework"
  }

  filter "configurations:Debug"
    defines "GG_DEBUG"
    runtime "Debug"
    symbols "on"
    
  filter "configurations:Release"
    defines "GG_RELEASE"
    runtime "Release"
    optimize "on"
    
  filter "configurations:Dist"
    defines "GG_DIST"
    runtime "Release"
    optimize "on"
