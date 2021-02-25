#include "Time.hpp"

float Time::deltaTime = 0;
Time::Time(){
    last_time = glfwGetTime();
}

float Time::GetTime(){
    return glfwGetTime();
}

void Time::UpdateTime(){
    Time::deltaTime = glfwGetTime() - last_time;
    last_time = glfwGetTime();
}



