#include "DataManager.hpp"
//All includes but scene

#include "Objects/Object.hpp"
#include "Objects/GameObject.hpp"

#include "Resources/Model.hpp"
#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"

#include "Objects/Mesh.hpp"
#include "Objects/SpriteAtlas.hpp"

#include "Components/Camera.hpp"

void ObjectLoader::LoadResources(const std::string& resources_path){
        //Creating models-----------------------------------------------------
        Model* square_model = new Model(DefaultShapes::SquareWithTex());
        Model* cube_model = new Model(DefaultShapes::CubeWithTex());
        Object::AddObjectBack(dynamic_cast<Resource*>(square_model));
        Object::AddObjectBack(dynamic_cast<Resource*>(cube_model));
        //--------------------------------------------------------------------
        Texture* sprite_sheet = new Texture("resources/images/sprite_sheet.png");
        Texture* omni_sprite = new Texture("resources/images/omnipothead.png");
        Texture* follow_sprite = new Texture("resources/images/spooky.png");
        Object::AddObjectBack(dynamic_cast<Resource*>(sprite_sheet));
        Object::AddObjectBack(dynamic_cast<Resource*>(omni_sprite));
        //--------------------------------------------------------------------
        Shader* atlas_shader = new Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/sprite.frag");
        atlas_shader->object_name = "MyAtlasShader";
        Shader* mesh_shader = new Shader ("resources/shaders/vertex/basic.vert","resources/shaders/fragment/sprite.frag");
        mesh_shader->object_name = "MyNormalShader";
        Object::AddObjectBack(dynamic_cast<Resource*>(atlas_shader));
        Object::AddObjectBack(dynamic_cast<Resource*>(mesh_shader));
        SpriteAtlas* sprite_atlas = new SpriteAtlas(sprite_sheet,1,3);
        sprite_atlas->object_name = "MySpriteAtlas" ;
        Object::AddObjectBack(dynamic_cast<Object*>(sprite_atlas));
        //--------------------------------------------------------------------
        Mesh* a_mesh = new Mesh(square_model,sprite_sheet);
        a_mesh->object_name = "CoolPlaneAtlas";
        Object::AddObjectBack(dynamic_cast<Object*>(a_mesh));

        a_mesh = new Mesh(square_model,omni_sprite);
        a_mesh->object_name = "CoolPlaneNormal";
        Object::AddObjectBack(dynamic_cast<Object*>(a_mesh));
        Object::AddObjectBack(dynamic_cast<Object*>(new Mesh(cube_model,follow_sprite)));
}

using namespace nlohmann;

SceneData ObjectLoader::LoadScene(const std::string& scene_path){
        std::ifstream i_f(scene_path);
        //Checks if the file exists
        if(!i_f){
                #ifdef DEBUG
                std::cout<< "Failed to load scene file!\n";
                #endif
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_LOADING_SCENE_FAIL,&scene_path);
                return SceneData{};
        }
        //Loads file into program
        SceneData scene_data;
        json j;
        i_f >> j;
        scene_data.scene_name = j["SceneInfo"]["SceneName"].get<std::string>();
        #ifdef DEBUG
        std::cout<<"Loading " << scene_data.scene_name << " scene.\n";
        #endif
        //Checks if there is data in scene
        if(!j.contains("SceneData")){
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_NODATA_SCENE_WARN,&scene_path);
                return scene_data;
        }
        json j_game_objects = j["SceneData"];
        if(!j_game_objects.contains("GameObjects")){
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_NODATA_SCENE_WARN,&scene_path);
                return scene_data;
        }  
        j_game_objects = j_game_objects["GameObjects"];
        for(json::iterator j_go = j_game_objects.begin(); j_go != j_game_objects.end(); j_go++){
                GameObject* go = new GameObject();
                if(j_go.value().contains("ObjectName")){
                        go->object_name = j_go.value()["ObjectName"].get<std::string>();
                }
                if(j_go.value().contains("ObjectComponents")){
                        json j_go_comps = j_go.value()["ObjectComponents"];
                        for(json::iterator j_comp = j_go_comps.begin() ; j_comp != j_go_comps.end() ; j_comp++){
                                json::object_t obj = j_comp.value().get<json::object_t>();
                                if(strcmp(obj.begin()->first.data(),"Transform") == 0){
                                        *go->transform = ComponentFactory::CreateTransform(obj.begin()->second,scene_path);
                                }
                                else{
                                        Component* comp = MakeComponent(obj.begin()->first, obj.begin()->second, scene_path);
                                        if(comp){
                                                go->PushComponentBack(comp);
                                        }   
                                }

                        }
                }
                if(j_go.value().contains("IsMainCamera")){
                        if(j_go.value()["IsMainCamera"].get<bool>()){
                                if(Camera* camera = go->GetComponent<Camera>()){
                                        scene_data.main_camera = camera;
                                }
                        }
                }
                scene_data.AddGameObject(go);
        }
        return scene_data;
}


Component* ObjectLoader::MakeComponent(json j_component, json j_values,const std::string& file_name){
        //Checks if component factory exists
        if(ComponentFactory::components_factories.find(j_component.get<std::string>()) == ComponentFactory::components_factories.end()){
                std::string params[] = {file_name,j_component.get<std::string>()};
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_NO_COMPONENT_FACTOR_FAIL,params);
                return nullptr;
        }
        //Returns from function factory
        return ComponentFactory::components_factories[j_component.get<std::string>()](j_values,file_name);
}

        // GameObject* go = new GameObject();
        // SceneData init_scene;
        // go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::objects[7]), dynamic_cast<Shader*>(Object::objects[4]),dynamic_cast<SpriteAtlas*>(Object::objects[6] ),0,0));
        // go->object_name = "first tile floor";
        // go->transform->SetPos(Vector3(0.0,0.5,0.0));
        // init_scene.AddGameObject(go);

        // go = new GameObject();
        // go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::objects[7]), dynamic_cast<Shader*>(Object::objects[4]),dynamic_cast<SpriteAtlas*>(Object::objects[6] ),0,0));
        // go->transform->SetPos(Vector3(1.0,0.5,0.0));
        // init_scene.AddGameObject(go);

        // go = new GameObject();
        // go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::objects[7]), dynamic_cast<Shader*>(Object::objects[4]),dynamic_cast<SpriteAtlas*>(Object::objects[6]),1,0));
        // go->PushComponentBack(new MovingObject());
        // go->transform = new Transform(Vector3(-1.5,0.5,0.5),Vector3(0.0,Math::ToRadians(90),0.0),Vector3(1.0,1.0,1.0));
        // init_scene.AddGameObject(go);

        // go = new GameObject();
        // go->object_name = "Camera Follower";
        // go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::objects[8]),dynamic_cast<Shader*>(Object::objects[5])));
        // go->PushComponentBack(new ObjectFollower());
        // go->transform->SetPos(Vector3(0.0,1.5,0.5));
        // init_scene.AddGameObject(go);

        // go = new GameObject();
        // go->PushComponentBack(new MeshRenderer(dynamic_cast<Mesh*>(Object::objects[9]),dynamic_cast<Shader*>(Object::objects[5])));
        // //go->PushComponentBack(new HeadFollower());
        // go->PushComponentBack(new RotateCubeQuat());
        // go->transform->position = Vector3(0.0,1.5,0.5);
        // init_scene.AddGameObject(go);


        // //Camera has to be added last to avoid weird de-sync rendering
        // go = new GameObject();
        // go->object_name = "Main Camera";
        // go->transform->SetPos(Vector3(0.0,1.0,5.0));
        // //Creates a camera and sets up projection configuration
        // Camera* a_camera = new Camera(Camera_Projection::PERSPECTIVE_PROJECTION);
        // go->PushComponentBack(a_camera);
        // go->PushComponentBack(new CameraMovement());
        // init_scene.main_camera = a_camera; 
        // init_scene.AddGameObject(go);

        // return init_scene;