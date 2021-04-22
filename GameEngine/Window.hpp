#pragma once
#include "GMpch.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameObject;
class Scene;

struct CursorInfo{
    int x_pos;
    int y_pos;
};

class Window{
    typedef void(*window_framebuffer)(Window* ,int, int);
    public:
        static Window* main_window;
        Window(unsigned int width, unsigned int height,std::string game_name);
        GLFWwindow* window;
        int width;
        int height;
        //-------------------
        //Input stuff--------
        CursorInfo cursor_info;
    private:
        static void FrameBufferCallBack(GLFWwindow* window, int width, int height);
        static void CursorPosCallBack(GLFWwindow* window,double xpos, double ypos);
};