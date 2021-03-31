#pragma once
#include "GMpch.hpp"
#include <GLFW/glfw3.h>
//Keep track of game time
class Time{
    public:
        Time();
        void UpdateTime();
        static float GetTime();
        static float deltaTime;
    private:
        float last_time =0;
};