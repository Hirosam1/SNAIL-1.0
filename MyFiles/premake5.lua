workspace "SnailEngine"
    configurations {"Debug", "Release"}

project "ExecutableGame"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    cppdialect "C++14"
    
    files {"include/*.hpp","src/*.cpp","../thirdparty/json/json.cpp","../thirdparty/glad/glad.cpp"}
    includedirs {"include/","../thirdparty/","../GameEngine/"}
    libdirs{"../thirdparty/GLFW","../thirdparty/portaudio"}
    if os.istarget("windows") then
        links{"glfw3", "gdi32", "GameEngine"}

    elseif os.istarget("linux") then
        links{"glfw3", "dl" ,"m", "GL", "GLU", "X11", "asound","pthread","GameEngine"}
    else 
        print("Can't support os")
    end
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