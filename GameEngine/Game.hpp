#pragma once
#include "GMpch.hpp"
#include "GameEngine.hpp"
#include "Behaviours.hpp"

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
                if(Object::all_objects[i]){
                    Object::all_objects[i]->UnloadObject();
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
                //Creating models-----------------------------------------------------
                Model* square_model = new Model(DefaultShapes::SquareWithTex());
                Model* cube_model = new Model(DefaultShapes::CubeWithTex());
                Resource::all_objects[0] = dynamic_cast<Resource*>(square_model);
                Resource::all_objects[1] = dynamic_cast<Resource*>(cube_model);
                //--------------------------------------------------------------------
                Texture* sprite_sheet = new Texture("resources/images/sprite_sheet.png");
                Texture* omni_sprite = new Texture("resources/images/omnipothead.png");
                Texture* follow_sprite = new Texture("resources/images/spooky.png");
                Resource::all_objects[2] = dynamic_cast<Resource*>(sprite_sheet);
                Resource::all_objects[3] = dynamic_cast<Resource*>(omni_sprite);
                //--------------------------------------------------------------------
                Shader* atlas_shader = new Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/sprite.frag");
                Shader* mesh_shader = new Shader ("resources/shaders/vertex/basic.vert","resources/shaders/fragment/sprite.frag");
                Resource::all_objects[4] = dynamic_cast<Resource*>(atlas_shader);
                Resource::all_objects[5] = dynamic_cast<Resource*>(mesh_shader);
                SpriteAtlas* sprite_atlas = new SpriteAtlas(sprite_sheet,1,3);
                Object::all_objects[6] = dynamic_cast<Object*>(sprite_atlas);
                //--------------------------------------------------------------------
                Object::all_objects[7] = dynamic_cast<Object*>(new Mesh(square_model,sprite_sheet));
                Object::all_objects[8] = dynamic_cast<Object*>(new Mesh(square_model,omni_sprite));
                Object::all_objects[9] = dynamic_cast<Object*>(new Mesh(cube_model,follow_sprite));
        }
        //Initiate the games objects with the components previously loaded
        void LoadGameObjects(){
            Scene* init_scene = new Scene();
            GameObject* go = new GameObject();
            go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::all_objects[7]), dynamic_cast<Shader*>(Object::all_objects[4]),dynamic_cast<SpriteAtlas*>(Object::all_objects[6] ),0,0));
            go->object_name = "first tile floor";
            go->transform->SetPos(Vector3(0.0,0.5,0.0));
            init_scene->AddGameObject(go);

            go = new GameObject();
            go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::all_objects[7]), dynamic_cast<Shader*>(Object::all_objects[4]),dynamic_cast<SpriteAtlas*>(Object::all_objects[6] ),0,0));
            go->transform->SetPos(Vector3(1.0,0.5,0.0));
            init_scene->AddGameObject(go);

            go = new GameObject();
            go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::all_objects[7]), dynamic_cast<Shader*>(Object::all_objects[4]),dynamic_cast<SpriteAtlas*>(Object::all_objects[6]),1,0));
            go->PushComponentBack(new MovingObject());
            go->transform = new Transform(Vector3(-1.5,0.5,0.5),Vector3(0.0,Math::ToRadians(90),0.0),Vector3(1.0,1.0,1.0));
            init_scene->AddGameObject(go);

            go = new GameObject();
            go->object_name = "Camera Follower";
            go->PushComponentBack(new MeshRenderer(dynamic_cast<Mesh*>(Object::all_objects[8]),dynamic_cast<Shader*>(Object::all_objects[5])));
            go->PushComponentBack(new ObjectFollower());
            go->transform->SetPos(Vector3(0.0,1.5,0.5));
            init_scene->AddGameObject(go);

            go = new GameObject();
            go->PushComponentBack(new MeshRenderer(dynamic_cast<Mesh*>(Object::all_objects[9]),dynamic_cast<Shader*>(Object::all_objects[5])));
            //go->PushComponentBack(new HeadFollower());
            go->PushComponentBack(new RotateCubeQuat());
            go->transform->position = Vector3(0.0,1.5,0.5);
            init_scene->AddGameObject(go);


            //Camera has to be added last to avoid weird de-sync rendering
            go = new GameObject();
            go->object_name = "Main Camera";
            go->transform->SetPos(Vector3(0.0,1.0,5.0));
            //Creates a camera and sets up projection configuration
            Camera* a_camera = new Camera(Camera_Projection::PERSPECTIVE_PROJECTION);
            go->PushComponentBack(a_camera);
            go->PushComponentBack(new CameraMovement());
            init_scene->main_camera = a_camera; 
            init_scene->AddGameObject(go);
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