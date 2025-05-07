workspace "GG"
  architecture "arm64"
  configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "GG/vendor/GLFW"

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

  -- libdirs "%{prj.name}/vendor/GLFW/deps"

  includedirs {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
    "%{prj.name}/vendor/GLFW/include"
  }

  -- defines {
  --   "_GLFW_COCOA"
  -- }

  -- links {
  --   -- "glfw3",
  --   "GLFW",
  -- }

  -- filter "system:macosx"
  links {
    
    "OpenGL.framework",
    -- "GLUT.framework",  -- 可选，用于简单窗口/渲染
    "Cocoa.framework",
    "IOKit.framework",
    -- "CoreFoundation.framework",
    -- "CoreGraphics.framework",
    "QuartzCore.framework",
    "GLFW",
      
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

  -- libdirs "GG/vendor/GLFW/deps"

  includedirs {
    "GG/vendor/spdlog/include",
    "GG/vendor/GLFW/include",
    "GG/src",
  }

  -- filter "kind:not StaticLib"
	-- 	links "glfw3"
	-- filter {}

  links {
    "GG",
    -- "GL",
      --   "Cocoa.framework",
      -- "IOKit.framework",
      -- "CoreFoundation.framework",
      -- "CoreGraphics.framework",
      -- "QuartzCore.framework"
  }

  -- filter "system:macosx"
  -- defines {
  --   "_GLFW_COCOA"
  -- }

  -- links {
  --     "Cocoa.framework",
  --     "IOKit.framework",
  --     "CoreFoundation.framework",
  --     "CoreGraphics.framework",
  --     "QuartzCore.framework"
  -- }

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