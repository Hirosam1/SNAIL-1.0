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
            //Benchmark windown init----------------------------------
            Timer window_time = Timer(&tes,"Window init");
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
            TraceEventsSession end_tes = TraceEventsSession("Terminating game");
            Timer timer = Timer(&end_tes,"Unloading resources");
            for(int i = 0; i < 4; i++){
                res_init[i]->UnloadResourse();
            }
            timer.Stop();
            Timer timer2 = Timer(&end_tes,"Terminating glfw window");
            glfwTerminate();
            timer2.Stop();
            end_tes.EndSession();
        }

    private:
        //Loads all the initial resources, and components
        void LoadResources(){
            
            //Creating models--------------------------------
            Model* square_model = new Model(DefaultShapes::SquareWithTex());
            res_init[0] = dynamic_cast<Resource*>(square_model);
            //--------------------------------------------------------------------
            Texture* sprite_sheet = new Texture("resources/images/sprite_sheet.png");
            res_init[1] = dynamic_cast<Resource*>(sprite_sheet);
            //--------------------------------------------------------------------
            Shader* atlas_shader = new Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/sprite.frag");
            res_init[2] = dynamic_cast<Resource*>(atlas_shader);
            SpriteAtlas* sprite_atlas = new SpriteAtlas(sprite_sheet,1,3);
            res_init[3] = dynamic_cast<Resource*>(sprite_atlas);
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
            go->transform = new Transform(Vector3(-1.5,0.0,0.5),Vector3(0.0,ToRadians(90),0.0),Vector3(1.0,1.0,1.0));
            o_list.push_back(dynamic_cast<Object*>(go));
            go = new GameObject();
            go->PushComponentBack(components_init[0]);
            go->transform->SetPos(Vector3(1.0,0.0,0.0));
            o_list.push_back(dynamic_cast<Object*>(go));
            //Creates a camera and sets up projection configuration
            Camera* a_camera = new Camera(Camera_Projection::PERSPECTIVE_PROJECTION);
            go = new GameObject();
            go->PushComponentBack(a_camera);
            a_camera->game_object->transform->SetPos(Vector3(0.0,0.0,1.0));
            Window::main_window->main_camera = a_camera; 
            o_list.push_back(dynamic_cast<Object*>(go));
            a_camera->game_object->object_name = "Main Camera";
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
                Sprite::draw_count = 0;
                glfwSwapBuffers(Window::main_window->window);
                glfwPollEvents();
            }
        }
        std::string game_name;
        TraceEventsSession tes = TraceEventsSession("Profile");
        //Pointers Holders
        Component* components_init[2];
        Resource* res_init[4];
        //Global funcs
        Time time;
        StateManager state_man;
        Window main_window;
        //flag that sets ready to start the game
        bool is_ready = false;
};