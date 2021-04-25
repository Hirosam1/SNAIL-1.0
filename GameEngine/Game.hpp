#pragma once
#include "GMpch.hpp"
#include "GameEngine.hpp"
#include "Behaviours.hpp"
#include "DataManager.hpp"

//Controlls general flow and management of the whole game
class Game {
    public:
        Game(const std::string& game_name, int screen_width, int screen_height) : game_name(game_name){
            #ifdef DEBUG
                std::cout<<std::fixed;
                // std::cout<<std::setprecision(4);
                std::cout<<"THIS IS DEBUG\n";
            #endif
            Debug::CleanErrorLog();
            //Benchmark windown init----------------------------------
            #ifdef DEBUG
            std::cout<<"Initializing Window\n";
            #endif
            Timer window_time = Timer(&tes,"Window init");
            Window* window = new Window(screen_width,screen_height,game_name);
            glfwSwapInterval(1);
            window_time.Stop();
            //-------------------------------------------------------- 
        }
        void InitGame(){
            #ifdef DEBUG
            std::cout<<"Loading Resources\n";
            #endif
            Timer res_load_time = Timer(&tes, "Resource loading");
            LoadResources();
            res_load_time.Stop();

            Timer res_obj_all_time = Timer(&tes, "Object and resource management");
            Timer obj_loading = Timer(&tes, "Object loading");
            #ifdef DEBUG
            std::cout<<"Loading GameObjects\n";
            #endif

            LoadGameObjects();

            obj_loading.Stop();
            res_obj_all_time.Stop();
            #ifdef DEBUG
            std::cout<<"Initializing Scene\n";
            #endif
            
            ObjectsInitialization();

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
            #ifdef DEBUG
            std::cout<<"Terminating game\n";
            #endif
            TraceEventsSession end_tes = TraceEventsSession("Terminating game");
            Timer _timer = Timer(&end_tes,"Unloading resources");
            for(int i = 0; i < 20; i++){
                if(Object::objects[i]){
                    Object::objects[i]->UnloadObject();
                }
            }
            _timer.Stop();
            Timer timer2 = Timer(&end_tes,"Terminating glfw window");
            glfwTerminate();
            timer2.Stop();
            end_tes.EndSession();
        }

    private:
        //Loads all the initial resources
        void LoadResources(){
            ObjectLoader::LoadResources("asd");
        }
        //Initiate the games objects with the components previously loaded
        void LoadGameObjects(){
            Scene* init_scene = new Scene("asd");
            Scene::active_scene = init_scene;
        }
        //Initiate the game objects created
        void ObjectsInitialization(){
            Scene::active_scene->BeginScene();
            glClearColor(0.02f,0.05,0.12,1.0);
        }
        //Loops until the game ends
        void Loop(){   
            //Main loop----------------------------------
            while(!glfwWindowShouldClose(Window::main_window->window)){
                time.UpdateTime();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                Scene::active_scene->UpdateScene();

                SpriteRenderer::draw_count = 0;
                MeshRenderer::draw_count = 0;
                
                glfwSwapBuffers(Window::main_window->window);
                glfwPollEvents();
            }
        }
        std::string game_name;
        TraceEventsSession tes = TraceEventsSession("Profile");
        //Global funcs
        Time time;
        StateManager state_man;
        //flag that sets ready to start the game
        bool is_ready = false;
};