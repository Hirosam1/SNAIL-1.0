#pragma once
#include "GMpch.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math.hpp"
#include "Matrix.hpp"

class Object;

struct WindowInfo{
    Matrix4 projection;
    float FOV = ToRadians(90.0f);
    float ortho_size = 3.0;
    //(float FOV, float aspect_ratio, float near, float far)
    Matrix4(*projection_function)(float,float ,float ,float, float);
};

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
        window_framebuffer frame_buffer_size_callback;
        WindowInfo window_info;
        int width;
        int height;
        std::list<Object*> object_list;
        CursorInfo cursor_info;
    private:
        static void FrameBufferCallBack(GLFWwindow* window, int width, int height);
        static void CursorPosCallBack(GLFWwindow* window,double xpos, double ypos);
};