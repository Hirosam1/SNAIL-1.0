#pragma once
#include "GMpch.hpp"
#include "GameEngine.hpp"
#include "CameraMovement.hpp"
#include "MovingObject.hpp"

class Game {
    public:
        Game(const std::string& game_name, int screen_width, int screen_height) : game_name(game_name), main_window(Window(screen_width,screen_height,game_name)){
            #ifdef DEBUG
                std::cout<<std::fixed;
                std::cout<<std::setprecision(4);
                std::cout<<"THIS IS DEBUG\n";
            #endif
            Debug::CleanErrorLog();
            //Benhmark windown init----------------------------------
            Timer window_time = Timer(&tes,"Window init");
            // glfwSetCursorPosCallback(window,mouse_callback);
            glfwSwapInterval(1);
            window_time.Stop();
            //-------------------------------------------------------- 
        }
        void InitGame(){
            Timer res_load_time = Timer(&tes, "Resource loading");
            LoadResources();
            res_load_time.Stop();

            Timer res_obj_all_time = Timer(&tes, "Object and resource management");
            Timer obj_loading = Timer(&tes, "Object loading");

            LoadGameObjects();

            obj_loading.Stop();

            ObjectsInitialization();

            res_obj_all_time.Stop();

            tes.EndSession(); 
            is_ready = true;
        }
        void RunGame(){
            if(is_ready){
                Loop();
            }
        }
        //Terminate the process
        void TerminateGame(){
            glfwTerminate();
        }

    private:
        //Loads all the initial resources, and components
        void LoadResources(){
            
            //Creating models--------------------------------
            square_model = new Model(DefaultShapes::SquareWithTex());
            //--------------------------------------------------------------------
            sprite_sheet = new Texture("resources/images/sprite_sheet.png");
            //--------------------------------------------------------------------
            atlas_shader = new Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/sprite.frag");
            sprite_atlas = new SpriteAtlas(sprite_sheet,1,3);
            //Floor
            components_init[0] = new Sprite(square_model,sprite_atlas,0,0,atlas_shader);
            //Rocky
            components_init[1] = new Sprite (square_model,sprite_atlas,1,0,atlas_shader);
            
            //--------------------------------------------------------------------
        }
        //Initiate the games objects with the components previously loaded
        void LoadGameObjects(){
            
            std::list<Object*>& o_list = Window::main_window->object_list;
            GameObject* go = new GameObject();
            go->PushComponentBack(new CameraMovement());
            go->object_name = "Camera movement";
            o_list.push_back(dynamic_cast<Object*>(go));
            go = new GameObject();
            go->PushComponentBack(components_init[0]);
            go->object_name = "first tile floor";
            o_list.push_back(dynamic_cast<Object*>(go));
            go = new GameObject();
            go->PushComponentBack(components_init[1]);
            go->PushComponentBack(new MovingObject());
            go->transform = new Transform(Vector3(-1.5,0.0,0.5),Vector3(0.0,-ToRadians(90),0.0),Vector3(1.0,1.0,1.0));
            o_list.push_back(dynamic_cast<Object*>(go));
            go = new GameObject();
            go->PushComponentBack(components_init[0]);
            go->transform->SetPos(Vector3(1.0,0.0,0.0));
            o_list.push_back(dynamic_cast<Object*>(go));
            //Creates a camera and sets up projection configuration
            Camera* a_camera = new Camera(Camera_Projection::PERSPECTIVE_PROJECTION);
            a_camera->SetCameraPos(Vector3(0.0,0.0,1.0));
            o_list.push_back(dynamic_cast<Object*>(a_camera));
            a_camera->object_name = "Main Camera";
            Window::main_window->main_camera = a_camera;       
        }
        //Initiate the game objects created
        void ObjectsInitialization(){
            for(Object* _go :  Window::main_window->object_list){
                _go->Begin();
            }

            glClearColor(0.02f,0.05,0.12,1.0);
        }
        //Loops until the game ends
        void Loop(){
            
            //Main loop----------------------------------
            while(!glfwWindowShouldClose(Window::main_window->window)){
                time.UpdateTime();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                for(Object* _go : Window::main_window->object_list){
                    _go->Update();
                }
                
                glfwSwapBuffers(Window::main_window->window);
                glfwPollEvents();
                
            }
        }
        std::string game_name;
        TraceEventsSession tes = TraceEventsSession("Profile");
        Component* components_init[2];
        //Resources !!Later Implement Resources abstract class!!----
        Shader* atlas_shader;
        SpriteAtlas* sprite_atlas;
        Model* square_model;
        Texture* sprite_sheet;
        //Global funcs
        Time time;
        StateManager state_man;
        Window main_window;
        //flag that sets ready to start the game
        bool is_ready = false;
};