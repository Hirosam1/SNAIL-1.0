project "GameEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    targetdir "bin/%{cfg.buildcfg}"
    files {"**.hpp","../thirdparty/*","src/**.cpp", "../thirdparty/glad/*.c"}

    includedirs {".","../thirdparty/"}
    filter "configurations:Debug"
        defines {"DEBUG", "F_PRECISION=3"}
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