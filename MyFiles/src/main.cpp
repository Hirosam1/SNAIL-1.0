#include "GameEngine.hpp"

#include "windows.h"

#ifdef DEBUG
    const bool debug = true;
    #ifdef F_PRECISION
    const int f_precision = F_PRECISION;
    #else
    const int f_precision = 4;
    #endif
#else
    const bool debug = false;
#endif

//calls when ever the size of the glfw window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//Proccess basic input
void processInput(GLFWwindow* window);

void framebuffer_callback(Window* window, int width, int height){
    window->window_info.projection = window->window_info.projection_function(window->window_info.FOV,width/(float)height,.15f,100.0f, window->window_info.ortho_size);
    glViewport(0,0,width,height);
}

//Set Consts
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;
//global variable

int fly_multiplier = 1;

int main(int argc, char** argv){
    #ifdef DEBUG
        std::cout<<std::fixed;
        std::cout<<std::setprecision(f_precision);
        std::cout<<"THIS IS DEBUG\n";
    #endif
    Debug::CleanErrorLog();
    bool is_full_screen = false;
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            fly_multiplier = strcmp(argv[i],"FPS=true") == 0? 0 : fly_multiplier;
            is_full_screen = strcmp(argv[i], "FullScreen=true") == 0? 1 : 0;
        }
    }
    
    Window* a_window = new Window(SCR_WIDTH,SCR_HEIGHT,"Engine Thing");
    a_window->frame_buffer_size_callback = framebuffer_callback;
    //Perspective Configuration---------------------------------------------
    a_window->window_info.projection_function = Projection::Orthographic;
    a_window->window_info.projection = a_window->window_info.projection_function(a_window->window_info.FOV,SCR_WIDTH/(float)SCR_HEIGHT,.15f,100.0f, a_window->window_info.ortho_size);
    // glfwSetCursorPosCallback(window,mouse_callback);
    glfwSwapInterval(1);
    //-----------------------------------------------------------------------------------------------------
    //Sets the viewport coordinates
    //The first two sets the coordinates of the lower left corner of the window

    //Creating models--------------------------------
    Model square_model(DefaultShapes::SquareWithTex());
    //--------------------------------------------------------------------
    Texture sprite_sheet = Texture("resources/images/sprite_sheet.png");
    //--------------------------------------------------------------------
    Shader sprite_shader = Shader("resources/shaders/vertex/basic.vert", "resources/shaders/fragment/sprite.frag");
    Shader atlas_shader = Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/sprite.frag");
    SpriteAtlas sprite_atlas = SpriteAtlas(&sprite_sheet,2,4);
    Sprite main_sprite = Sprite(&square_model,&sprite_atlas,0,0,&atlas_shader);
    Sprite car_sprite = Sprite(&square_model,&sprite_atlas,3,1,&atlas_shader);
    Sprite zombir_sprite = Sprite(&square_model,&sprite_atlas,2,0, &atlas_shader);
    //------------------------------------------------------------------------------------------------------------
    std::list<GameObject*> go_list = std::list<GameObject*>();
    a_window->go_list = &go_list;
    GameObject* go = new GameObject();
    go->PushComponentBack(&main_sprite);
    //go.PushComponentBack(new HeadScript());
    go_list.push_back(go);
    go = new GameObject();
    go->PushComponentBack(&car_sprite);
    go->transform->SetPos(Vector3(1.0f,0.0f,0.1f));
    go->object_name = "Car";
    go_list.push_back(go);
    go = new GameObject();
    go->PushComponentBack(&zombir_sprite);
    go->transform->SetPos(Vector3(-1,0,0));
    go_list.push_back(go);
    // Uniform names-----------------------------------------------------
    std::string view_str = "view";
    std::string projection_str = "projection";
    ///----------------------------
    Camera a_camera;
    a_camera.SetCameraPos(Vector3(0.0,0.0,1.0));
    Time time;
    //Kill cursor----------
    //glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glClearColor(0.02f,0.05,0.12,1.0);
    for(GameObject* _go : go_list){
        _go->Begin();
    }
    //Main loop----------------------------------
    //Shader and texture bindings should be done on a state manager
    atlas_shader.UseShader();
    std::string text1_str = "Texture1";
    sprite_atlas.texture->UseTexture(atlas_shader,text1_str,0);
    while(!glfwWindowShouldClose(Window::main_window->window)){
        time.UpdateTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        a_camera.BuildMat();
        atlas_shader.SetUniformMatrix4f(view_str,a_camera.View().GetPtr());
        atlas_shader.SetUniformMatrix4f(projection_str,Window::main_window->window_info.projection.GetPtr());

        for(GameObject* _go : go_list){
            _go->Update();
        }

        glfwSwapBuffers(Window::main_window->window);
        glfwPollEvents();
        processInput(Window::main_window->window);
    }
    //-------------------------------------------
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}


void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}


