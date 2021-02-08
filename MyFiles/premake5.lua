workspace "HelloWorld"
    configurations {"Debug", "Release", "Clang"}

project "HelloWorld"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    cppdialect "C++14"
    
    files {"include/*.hpp","src/*.cpp"}
    includedirs {"include/","../thirdparty/","../GameEngine/"}
    libdirs{"../thirdparty/GLFW"}
    links{"glfw3", "gdi32", "GameEngine"}
    filter "configurations:Debug"
        kind "ConsoleApp"
        defines {"DEBUG"}
        symbols "On"
        optimize "Off"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    filter "configurations:Clang"
        defines {"DEBUG"}
        symbols "On"
        optimize "Off"
        toolset "clang"

include "../GameEngine"