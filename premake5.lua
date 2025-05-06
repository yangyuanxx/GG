workspace "GG"
  architecture "arm64"
  configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GG"
  location "GG"
  kind "SharedLib"
  language "C++"

  cppdialect "C++17"
  
  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  -- precompiled header，加速编译
  pchheader "ggpch.h"
  pchsource "Engine/src/ggpch.cpp"

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  includedirs {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include"
  }

  filter "configurations:Debug"
    defines "GG_DEBUG"
    runtime "Debug"
    symbols "On"
    
  filter "configurations:Release"
    defines "GG_RELEASE"
    runtime "Release"
    optimize "On"
    
  filter "configurations:Dist"
    defines "GG_DIST"
    runtime "Release"
    optimize "On"

project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"

  cppdialect "C++17"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  includedirs {
    "GG/vendor/spdlog/include",
    "GG/src"
  }

  links {
    "GG"
  }

  filter "configurations:Debug"
    defines "GG_DEBUG"
    runtime "Debug"
    symbols "On"
    
  filter "configurations:Release"
    defines "GG_RELEASE"
    runtime "Release"
    optimize "On"
    
  filter "configurations:Dist"
    defines "GG_DIST"
    runtime "Release"
    optimize "On"