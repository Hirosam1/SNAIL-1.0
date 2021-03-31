#include "GameEngine.hpp"
#include "CameraMovement.hpp"
#include "MovingObject.hpp"
#include "EventTracer.hpp"
#include "GMpch.hpp"

#ifdef DEBUG
    #ifdef F_PRECISION
    const int f_precision = F_PRECISION;
    #else
    const int f_precision = 4;
    #endif
#else
    const bool debug = false;
#endif

//Start benchmarking session-------------------------
TraceEventsSession tes = TraceEventsSession("Profile");
int count_new = 0;

// void* operator new(size_t size){
//     void* ptr = malloc(size);
//     if (!ptr){
//         std::bad_alloc ba;
//         std::cout<<"Memory allocation error\n";
//         throw ba;
//     }
//     std::cout<<"Memory allocated "<<++count_new <<"\n";
//     //InstantEvent::CreateInstantEvent(&tes,"Memory allocation: " + size);
//     return ptr;
// }

// void operator delete(void* ptr){
//     std::cout<<"Memory deallocated "<<--count_new <<"\n";
//     free(ptr);
// }

// void operator delete[](void* ptr){
//     std::cout<<"Memory deallocated "<<--count_new <<"\n";
//     free(ptr);
// }

//Proccess basic input
void processInput(GLFWwindow* window);
//Set Consts
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;
int main(int argc, char** argv){
    #ifdef DEBUG
        std::cout<<std::fixed;
        std::cout<<std::setprecision(f_precision);
        std::cout<<"THIS IS DEBUG\n";
    #endif
    Debug::CleanErrorLog();
    //Benhmark windown init----------------------------------
    Timer window_time = Timer(&tes,"Window init");
    Window* a_window = new Window(SCR_WIDTH,SCR_HEIGHT,"Engine Thing");
    // glfwSetCursorPosCallback(window,mouse_callback);
    glfwSwapInterval(1);
    window_time.Stop();
    //-----------------------------------------------------------------------------------------------------
    //Benchmark resource loading---------------------------
    Timer res_obj_all_time = Timer(&tes, "Object and resource management");
    Timer res_load_time = Timer(&tes, "Resource loading");
    //Creating models--------------------------------
    Model square_model(DefaultShapes::SquareWithTex());
    //--------------------------------------------------------------------
    Texture sprite_sheet = Texture("resources/images/sprite_sheet.png");
    //--------------------------------------------------------------------
    Shader atlas_shader = Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/sprite.frag");
    SpriteAtlas sprite_atlas = SpriteAtlas(&sprite_sheet,1,3);
    Sprite floor_sprite = Sprite(&square_model,&sprite_atlas,0,0,&atlas_shader);
    Sprite rocky_sprite = Sprite (&square_model,&sprite_atlas,1,0,&atlas_shader);
    res_load_time.Stop();
    //-----------------------------------------------------------------------------------------------------
    Timer obj_loading = Timer(&tes, "Object loading");
    std::list<Object*>& o_list = a_window->object_list;
    GameObject* go = new GameObject();
    go->PushComponentBack(new CameraMovement());
    o_list.push_back(dynamic_cast<Object*>(go));
    go = new GameObject();
    go->PushComponentBack(&floor_sprite);
    o_list.push_back(dynamic_cast<Object*>(go));
    go = new GameObject();
    go->PushComponentBack(&rocky_sprite);
    go->PushComponentBack(new MovingObject());
    go->transform = new Transform(Vector3(-1.5,0.0,0.5),Vector3(0.0,-ToRadians(90),0.0),Vector3(1.0,1.0,1.0));
    o_list.push_back(dynamic_cast<Object*>(go));
    go = new GameObject();
    go->PushComponentBack(&floor_sprite);
    go->transform->SetPos(Vector3(1.0,0.0,0.0));
    o_list.push_back(dynamic_cast<Object*>(go));
    obj_loading.Stop();
    res_obj_all_time.Stop();
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
    {
        Timer init_ojects = Timer(&tes, "Objects initialization");
        for(Object* _go : o_list){
            _go->Begin();
        }
    }
    tes.EndSession();
    
    //Main loop----------------------------------
    //Shader and texture bindings should be done on a state manager
    atlas_shader.UseShader();
    std::string text1_str = "Texture1";
    sprite_atlas.texture->UseTexture(atlas_shader,text1_str,0);
    unsigned int frame_c = 0;
    std::string frame_str = "frame update";
    while(!glfwWindowShouldClose(Window::main_window->window)){
        // std::string timer_str = "frame(" + std::to_string(++frame_c) + ")";
        // Timer timer = Timer(&tes, frame_str);
        time.UpdateTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Sprite::draw_count = 0;
        for(Object* _go : a_window->object_list){
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

void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}


