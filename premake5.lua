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

group "Dependencies"
    include "LearningVulkan/vendor/GLFW"

group""

project "LearningVulkan"
    location "LearningVulkan"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

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
    }

    links
    {
      "GLFW",
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