#pragma once
#include "GMpch.hpp"
#include "GameEngine.hpp"
#include "Behaviors.hpp"
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
            Timer res_load_time = Timer(&tes, "Resource indexing");
            LoadResources();
            res_load_time.Stop();

            Timer obj_loading = Timer(&tes, "Scene/Resource loading");

            LoadScene();

            obj_loading.Stop();
            #ifdef DEBUG
            std::cout<<"Initializing Scene\n";
            #endif
            Timer obj_init = Timer(&tes,"Object initialization");
            ObjectsInitialization();
            obj_init.Stop();

            tes.EndSession(); 
            is_ready = true;
        }
        void RunGame(){
            if(is_ready){
                MainLoop();
            }
        }
        //Terminate the process
        void TerminateGame(){
            #ifdef DEBUG
            std::cout<<"Terminating game\n";
            #endif
            TraceEventsSession end_tes = TraceEventsSession("Terminating game");
            Timer _timer = Timer(&end_tes,"Unloading resources");
            Scene::active_scene->UnloadScene();
            _timer.Stop();
            Timer timer2 = Timer(&end_tes,"Terminating glfw window");
            glfwTerminate();
            timer2.Stop();
            end_tes.EndSession();
        }

    private:
        //Loads all the initial resources
        void LoadResources(){
            ObjectLoader::LoadResources("Resources.sres.json");
        }
        //Loads inital scene, can be used as a sandbox place to start the scene
        void LoadScene(){
            Scene* init_scene = new Scene(ResourcesInfo::starting_scene_path);
            Scene::active_scene = init_scene;
            //========== SANDBOX ADD GAMEOBJECTS TO INIT_SCENE ==============
            //========== END  ==============================================
        }
        //Initiate the game objects created
        void ObjectsInitialization(){
            Scene::active_scene->BeginScene();
            glClearColor(0.02f,0.05,0.12,1.0);
        }
        //Loops until the game ends
        void MainLoop(){   
            //Main loop----------------------------------
            while(!glfwWindowShouldClose(Window::main_window->window)){
                time.UpdateTime();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                Scene::active_scene->UpdateScene();
                Renderer::draw_count = 0;
                //Testing the glFinish thing
                glFinish();
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