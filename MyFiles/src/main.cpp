#include "GameEngine.hpp"
#include "windows.h"
#include "CameraMovement.hpp"

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

//Proccess basic input
void processInput(GLFWwindow* window);
\
void framebuffer_callback(Window* window, int width, int height){

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
    SpriteAtlas sprite_atlas = SpriteAtlas(&sprite_sheet,1,3);
    Sprite floor_sprite = Sprite(&square_model,&sprite_atlas,0,0,&atlas_shader);
    Sprite rocky_sprite = Sprite (&square_model,&sprite_atlas,1,0,&atlas_shader);
    //------------------------------------------------------------------------------------------------------------
    std::list<Object*>& o_list = a_window->object_list;
    GameObject* go = new GameObject();
    go->PushComponentBack(new CameraMovement());
    o_list.push_back(dynamic_cast<Object*>(go));
    go = new GameObject();
    go->PushComponentBack(&floor_sprite);
    o_list.push_back(dynamic_cast<Object*>(go));
    go = new GameObject();
    go->PushComponentBack(&rocky_sprite);
    go->transform = new Transform(Vector3(0.0,0.0,2.0),Vector3(0.0,ToRadians(180),0.0),Vector3(1.0,1.0,1.0));
    o_list.push_back(dynamic_cast<Object*>(go));
    go = new GameObject();
    go->PushComponentBack(&floor_sprite);
    go->transform->SetPos(Vector3(1.0,0.0,0.0));
    //o_list.push_back(dynamic_cast<Object*>(go));
    // Uniform names-----------------------------------------------------
    std::string view_str = "view";
    std::string projection_str = "projection";
    ///----------------------------
    //Creates a camera and sets up projection configuration
    Camera* a_camera = new Camera(Camera_Projection::PERSPECTIVE_PROJECTION);
    a_camera->SetCameraPos(Vector3(0.0,0.0,1.0));
    o_list.push_back(dynamic_cast<Object*>(a_camera));
    a_camera->object_name = "Main Camera";
    a_window->main_camera = &a_camera;
    Time time;    
    //glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glClearColor(0.02f,0.05,0.12,1.0);
    for(Object* _go : o_list){
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
        Sprite::draw_count = 0;
        for(Object* _go : a_window->object_list){
            _go->Update();
        }
        std::cout<<"Sprites rendered->"<<Sprite::draw_count<<"\n";
        std::cout<<"FPS->"<<1/Time::deltaTime<<"\n";
        // std::cout<<"Frustum left: " << a_camera->Frustum().left.normal << "| " << a_camera->Frustum().left.d <<
        //  "\nFrustum right: " << a_camera->Frustum().right.normal << "| " << a_camera->Frustum().right.d <<"\n";
        glfwSwapBuffers(Window::main_window->window);
        glfwPollEvents();
        processInput(Window::main_window->window);
    }
    //-------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}


