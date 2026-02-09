workspace "LearningVulkan"
    architecture "x64"
    configurations 
    { 
      "Debug", 
      "Release", 
      "Dist"
    }
    startproject "LearningVulkan"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root
IncludeDir = {}
IncludeDir["GLFW"] = "LearningVulkan/vendor/GLFW/include"
IncludeDir["glm"] = "LearningVulkan/vendor/glm"
IncludeDir["Vulkan"] = "$(VULKAN_SDK)/Include"

group"Dependencies"
    include "LearningVulkan/vendor/GLFW"

project "LearningVulkan"
  location "LearningVulkan"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  staticruntime "on"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  libdirs {"$(VULKAN_SDK)/Lib"}
  
  files 
    { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/vendor/glm/glm/**.hpp",
      "%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
      "%{prj.name}/src",
      "%{IncludeDir.GLFW}",
      "%{IncludeDir.glm}",
      "%{IncludeDir.Vulkan}"
    }

    links
    {
      "GLFW",
      "vulkan-1.lib"
    }

    defines
    {
      "_CRT_SECURE_NO_WARNINGS"
    }
    
    filter "system:windows"
      systemversion "latest"

      defines
      {
        "GLFW_INCLUDE_VULKAN",
      }
      
      
    filter "configurations:Debug"
      defines { "LV_DEBUG" }
      runtime "Debug"
      symbols "on"

    filter "configurations:Release"
      defines { "LV_RELEASE" }
      runtime "Release"
      optimize "on"

    filter "configurations:Dist"
      defines { "LV_DIST" }
      runtime "Release"
      optimize "on"