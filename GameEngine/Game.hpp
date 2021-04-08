#pragma once
#include "GMpch.hpp"
#include "GameEngine.hpp"
#include "Behaviours.hpp"

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
            Timer _timer = Timer(&end_tes,"Unloading resources");
            for(int i = 0; i < 7; i++){
                res_init[i]->UnloadResourse();
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
            //Creating models--------------------------------
            Model* square_model = new Model(DefaultShapes::SquareWithTex());
            Model* cube_model = new Model(DefaultShapes::CubeWithTex());
            res_init[0] = dynamic_cast<Resource*>(square_model);
            res_init[1] = dynamic_cast<Resource*>(cube_model);
            //--------------------------------------------------------------------
            Texture* sprite_sheet = new Texture("resources/images/sprite_sheet.png");
            Texture* spooky_sprite = new Texture("resources/images/spooky.png");
            res_init[2] = dynamic_cast<Resource*>(sprite_sheet);
            res_init[3] = dynamic_cast<Resource*>(spooky_sprite);
            //--------------------------------------------------------------------
            Shader* atlas_shader = new Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/sprite.frag");
            Shader* mesh_shader = new Shader ("resources/shaders/vertex/basic.vert","resources/shaders/fragment/sprite.frag");
            res_init[4] = dynamic_cast<Resource*>(atlas_shader);
            res_init[5] = dynamic_cast<Resource*>(mesh_shader);
            SpriteAtlas* sprite_atlas = new SpriteAtlas(sprite_sheet,1,3);
            res_init[6] = dynamic_cast<Resource*>(sprite_atlas);
            //--------------------------------------------------------------------
            res_init[7] = dynamic_cast<Resource*>(new Mesh(square_model,sprite_sheet));
            res_init[8] = dynamic_cast<Resource*>(new Mesh(square_model,spooky_sprite));
        }
        //Initiate the games objects with the components previously loaded
        void LoadGameObjects(){
            std::list<Object*>& o_list = Window::main_window->object_list;
            GameObject* go = new GameObject();
            go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(res_init[7]), dynamic_cast<Shader*>(res_init[4]),dynamic_cast<SpriteAtlas*>(res_init[6]),0,0));
            go->object_name = "first tile floor";
            o_list.push_back(dynamic_cast<Object*>(go));

            go = new GameObject();
            go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(res_init[7]), dynamic_cast<Shader*>(res_init[4]),dynamic_cast<SpriteAtlas*>(res_init[6]),0,0));
            go->transform->SetPos(Vector3(1.0,0.0,0.0));
            o_list.push_back(dynamic_cast<Object*>(go));

            go = new GameObject();
            go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(res_init[7]), dynamic_cast<Shader*>(res_init[4]),dynamic_cast<SpriteAtlas*>(res_init[6]),1,0));
            go->PushComponentBack(new MovingObject());
            go->transform = new Transform(Vector3(-1.5,0.0,0.5),Vector3(0.0,ToRadians(90),0.0),Vector3(1.0,1.0,1.0));
            o_list.push_back(dynamic_cast<Object*>(go));

            go = new GameObject();
            go->object_name = "Creepy Follower";
            go->PushComponentBack(new MeshRenderer(dynamic_cast<Mesh*>(res_init[8]),dynamic_cast<Shader*>(res_init[5])));
            go->PushComponentBack(new ObjectFollower());
            go->transform->SetPos(Vector3(0.0,1.0,0.0));
            o_list.push_back(dynamic_cast<Object*>(go));

            //Camera has to be added last to avoid weird de-sync rendering
            go = new GameObject();
            //Creates a camera and sets up projection configuration
            Camera* a_camera = new Camera(Camera_Projection::PERSPECTIVE_PROJECTION);
            go->PushComponentBack(a_camera);
            a_camera->game_object->transform->SetPos(Vector3(0.0,0.0,1.0));
            go->PushComponentBack(new CameraMovement());
            go->object_name = "Camera movement"; 
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

                SpriteRenderer::draw_count = 0;
                MeshRenderer::draw_count = 0;

                glfwSwapBuffers(Window::main_window->window);
                glfwPollEvents();
            }
        }
        std::string game_name;
        TraceEventsSession tes = TraceEventsSession("Profile");
        //Pointers Holders
        Resource* res_init[10];
        //Global funcs
        Time time;
        StateManager state_man;
        Window main_window;
        //flag that sets ready to start the game
        bool is_ready = false;
};