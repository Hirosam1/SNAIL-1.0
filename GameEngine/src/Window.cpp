#include "Window.hpp"
//#include "GameObject.hpp"
Window* Window::main_window = nullptr;

Window::Window(unsigned int width, unsigned int height, std::string game_name){
    if(!Window::main_window){
        this->width = width;
        this->height = height;
        object_list = std::list<Object*>();
        glfwInit();
        //Set upo version of openGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        //Only use 3.3 none backwards compatiblity
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //If we are using MacOS
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        //Create the window object
        window =glfwCreateWindow(width,height,game_name.data(), NULL,NULL);
        //GLFWwindow* window =glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Hello Window", is_full_screen ? glfwGetPrimaryMonitor(): NULL,NULL);
        glfwMakeContextCurrent(window);
        main_window = this;
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout<<"Failed to initialize GLAD\n";
        }
        glfwSetFramebufferSizeCallback(window,this->FrameBufferCallBack);
        glfwSetCursorPosCallback(window,this->CursorPosCallBack);
        glfwSetWindowUserPointer(window,static_cast<void*>(this));
        glViewport(0,0,width,height);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }
}

void Window::FrameBufferCallBack(GLFWwindow* window,int width,int height){
    Window* _window =  static_cast<Window*>(glfwGetWindowUserPointer(window));
    _window->width = width;
    _window->height = height;
    _window->frame_buffer_size_callback(_window,width,height);
}

void Window::CursorPosCallBack(GLFWwindow* window,double xpos, double ypos){
    Window* _window =  static_cast<Window*>(glfwGetWindowUserPointer(window));
    _window->cursor_info.x_pos = xpos;
    _window->cursor_info.y_pos = ypos;
}