language "C++"

workspace "sdlario"
    configurations { "release", "debug" }
    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:release"
        optimize "On"
    filter {}

    platforms { "Linux64", "Win64", "Linux32", "Win32", "OSX" }
    filter { "platforms:*32" }
        architecture "x86"
    filter { "platforms:Linux*" }
        kind "None"
        system "linux"
    filter { "platforms:Win*" }
        kind "WindowedApp"
        system "windows"
    filter { "platforms:OSX" }
        kind "WindowedApp"
        system "macosx"
        architecture "universal"
    filter {}
    
project "mario"
    files { "src/**.cpp" }
    targetdir "build/%{cfg.platform}_%{cfg.buildcfg}"
    objdir "build/%{cfg.platform}_%{cfg.buildcfg}/obj"
    includedirs { "./third-party/include" }
    links { "SDL2" }