workspace "SnailEngine"
    configurations {"Debug", "Release"}

project "ExecutableGame"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    cppdialect "C++14"
    
    files {"include/*.hpp","src/*.cpp","../thirdparty/json/json.cpp"}
    includedirs {"include/","../thirdparty/","../GameEngine/"}
    libdirs{"../thirdparty/GLFW"}
    links{"glfw3", "gdi32", "GameEngine"}
    filter "configurations:Debug"
        kind "ConsoleApp"
        defines {"DEBUG"}
        symbols "On"
        optimize "Off"
    filter "configurations:Release"
        kind "WindowedApp"
        defines { "NDEBUG" }
        optimize "On"

include "../GameEngine"