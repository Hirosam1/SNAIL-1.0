#pragma once
#include <GLFW/glfw3.h>

class Time{
    public:
        Time();
        void UpdateTime();
        static float GetTime();
        static float deltaTime;
    private:
        float last_time =0;
};