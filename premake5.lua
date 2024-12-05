language "C++"

workspace "sdlario"
    configurations { "debug", "release" }
    platforms { "Linux", "Win64", "OSX" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:release"
        optimize "Full"
    filter {}

    includedirs { "./third-party/**/include" }
    
project "SDL2"
    language "C"
    kind "StaticLib"
    files {
        "third-party/SDL2/src/*.c",
	    "third-party/SDL2/src/atomic/*.c",
	    "third-party/SDL2/src/audio/*.c",
	    "third-party/SDL2/src/audio/dummy/*.c",
	    "third-party/SDL2/src/cpuinfo/*.c",
	    "third-party/SDL2/src/events/*.c",
	    "third-party/SDL2/src/file/*.c",
	    "third-party/SDL2/src/haptic/*.c",
	    "third-party/SDL2/src/haptic/dummy/*.c",
	    "third-party/SDL2/src/hidapi/*.c",
	    "third-party/SDL2/src/joystick/*.c",
	    "third-party/SDL2/src/joystick/dummy/*.c",
	    "third-party/SDL2/src/loadso/dummy/*.c",
	    "third-party/SDL2/src/power/*.c",
	    "third-party/SDL2/src/filesystem/dummy/*.c",
	    "third-party/SDL2/src/locale/*.c",
	    "third-party/SDL2/src/locale/dummy/*.c",
	    "third-party/SDL2/src/misc/*.c",
	    "third-party/SDL2/src/misc/dummy/*.c",
	    "third-party/SDL2/src/render/*.c",
	    "third-party/SDL2/src/render/software/*.c",
	    "third-party/SDL2/src/sensor/*.c",
	    "third-party/SDL2/src/sensor/dummy/*.c",
	    "third-party/SDL2/src/stdlib/*.c",
	    "third-party/SDL2/src/libm/*.c",
	    "third-party/SDL2/src/thread/*.c",
	    "third-party/SDL2/src/thread/generic/*.c",
	    "third-party/SDL2/src/timer/*.c",
	    "third-party/SDL2/src/timer/dummy/*.c",
	    "third-party/SDL2/src/video/*.c",
	    "third-party/SDL2/src/video/yuv2rgb/*.c",
	    "third-party/SDL2/src/video/dummy/*.c",
		"third-party/SDL2/src/**.h"
    }
    targetdir "build/%{cfg.platform}_%{cfg.buildcfg}/lib/SDL2"
    objdir "build/%{cfg.platform}_%{cfg.buildcfg}/lib/SDL2/obj"
    
project "mario"
    kind "WindowedApp"
    links { "SDL2" }
    files { "src/**.cpp" }
    targetdir "build/%{cfg.platform}_%{cfg.buildcfg}"
    objdir "build/%{cfg.platform}_%{cfg.buildcfg}/obj"
    
