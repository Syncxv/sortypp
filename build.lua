
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


workspace "Sorting Algo Visualizer"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Sorting Algo Visualizer"
project "Sorting Algo Visualizer"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs { "deps/SDL2/include" }
   libdirs { "deps/SDL2/lib/x64" }

   links { "SDL2main", "SDL2" }

   targetdir ("./bin/" .. outputdir .. "/%{prj.name}")
   objdir ("./bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      postbuildcommands { "{COPY} \"%{wks.location}deps/SDL2/lib/x64/SDL2.dll\" \"%{cfg.targetdir}\"" }
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      postbuildcommands { "{COPY} \"%{wks.location}deps/SDL2/lib/x64/SDL2.dll\" \"%{cfg.targetdir}\"" }
      defines { "RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      postbuildcommands { "{COPY} \"%{wks.location}deps/SDL2/lib/x64/SDL2.dll\" \"%{cfg.targetdir}\"" }
      kind "WindowedApp"
      defines { "DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"