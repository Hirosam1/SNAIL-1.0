#include "DataManager.hpp"
//All includes but scene

#include "Objects/Object.hpp"
#include "Objects/GameObject.hpp"

#include "Components/Camera.hpp"

using namespace nlohmann;

void ObjectLoader::LoadResources(const std::string& resources_path){
        std::ifstream i_f(resources_path);
        //Checks if the file exists
        //Init singletons
        new ComponentFactory();
        new ResourcesInfo();
        new ObjectsInfo();
        //-------------

        if(!i_f){
                #ifdef DEBUG
                std::cout<< "Failed to load resource file!\n";
                #endif
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_LOADING_SCENE_FAIL,&resources_path);
                return;
        } 
        json j;
        i_f >> j;
        if(!j.contains("ResourceInfo")){
                Debug::WriteErrorLog(ErrorType::RESLOADER_NO_RESINFO_FAIL,&resources_path);
                return;
        }
        if(!j["ResourceInfo"].contains("ResourceName")){
                Debug::WriteErrorLog(ErrorType::RESLOADER_NO_RESINFO_FAIL,&resources_path);
                return;
        }
        if(j.contains("ResourceData")){
                json j_aux = j["ResourceData"];
                if(j_aux.contains("Shaders")){
                        //Get all shaders
                        for(json::iterator j_sh = j_aux["Shaders"].begin() ; j_sh != j_aux["Shaders"].end() ; j_sh++){
                                ResourcesInfo::ShaderInfo shader_info;
                                std::string shader_name;
                                std::string params[] = {resources_path,"Shader"};

                                if(FileIO::TryToRead(j_sh.value(),"Name",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&shader_name)){
                                if(FileIO::TryToRead(j_sh.value(),"VertexPath",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&shader_info.vertex_path)){
                                if(FileIO::TryToRead(j_sh.value(),"FragmentPath",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&shader_info.fragment_path)){         
                                        ResourcesInfo::singleton->shaders_map[shader_name] = shader_info;
                                }
                                }
                                }
                        }
                }
                if(j_aux.contains("Textures")){
                        std::string params[] = {resources_path,"Textures"};
                        std::string texture_name;
                        ResourcesInfo::TextureInfo tex_info;
                        for(json::iterator j_tex = j_aux["Textures"].begin() ; j_tex != j_aux["Textures"].end() ; j_tex++){
                                if(FileIO::TryToRead(j_tex.value(),"Name",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&texture_name)){
                                if(FileIO::TryToRead(j_tex.value(),"TexturePath",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&tex_info.texture_path)){
                                        ResourcesInfo::singleton->texture_map[texture_name] = tex_info;
                                }
                                }
                        }
                }
                if(j_aux.contains("Models")){
                        std::string params[] = {resources_path,"Models"};
                        std::string model_name;
                        ResourcesInfo::ModelInfo model_info;
                        for(json::iterator j_model = j_aux["Models"].begin() ; j_model != j_aux["Models"].end() ; j_model++){
                                if(FileIO::TryToRead(j_model.value(),"Name",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&model_name)){
                                int i;
                                if(FileIO::TryToRead(j_model.value(),"DefaultShape",ErrorType::NO_ERROR,nullptr,&i)){
                                        switch (i)
                                        {
                                        case 0:
                                                model_info.default_shape = 0;
                                                break;
                                        case 1:
                                                model_info.default_shape = 1;
                                                break;
                                        default:
                                                break;
                                        }
                                }
                                        ResourcesInfo::singleton->model_map[model_name] = model_info;
                                }
                        }
                }
        }
        if(j.contains("ObjectData")){
                json j_aux = j["ObjectData"];
                if(j_aux.contains("SpriteAtlas")){
                        std::string params[] = {resources_path,"SpariteAtlas"};
                        for(json::iterator j_spa = j_aux["SpriteAtlas"].begin() ; j_spa != j_aux["SpriteAtlas"].end(); j_spa++){
                                std::string atlas_name;
                                ObjectsInfo::SpriteAtlasInfo atlas_info;
                                std::vector<int> vec2;
                                if(FileIO::TryToRead(j_spa.value(),"Name",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&atlas_name)){
                                if(FileIO::TryToRead(j_spa.value(),"SheetTexture",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&atlas_info.sheet_texture_name)){
                                if(FileIO::TryToRead(j_spa.value(),"SheetDimensions",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&vec2)){
                                        atlas_info.atlas_dimensions = Vector2(vec2[0],vec2[1]);
                                        ObjectsInfo::singleton->sprite_atlas_map[atlas_name] = atlas_info;

                                }
                                }
                                }
                        }
                }
                if(j_aux.contains("Meshes")){
                        std::string params[] = {resources_path,"Meshes"};
                        for(json::iterator j_m = j_aux["Meshes"].begin() ; j_m != j_aux["Meshes"].end() ; j_m++){
                                std::string mesh_name;
                                ObjectsInfo::MeshInfo mesh_info;
                                if(FileIO::TryToRead(j_m.value(),"Name",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&mesh_name)){
                                if(FileIO::TryToRead(j_m.value(),"Model",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&mesh_info.model_name)){
                                if(FileIO::TryToRead(j_m.value(),"Texture",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&mesh_info.texture_name)){
                                        ObjectsInfo::singleton->meshes_map[mesh_name] = mesh_info;
                                }
                                }
                                }

                        }
                }
        }

}

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
        if(!j.contains("SceneInfo")){
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_NO_SCENE_INFO_FAIL,&scene_path);
                return scene_data;
        }
        if(!FileIO::TryToRead(j["SceneInfo"],"SceneName",ErrorType::OBJECTLOADER_NO_SCENE_INFO_FAIL,&scene_path,&scene_data.scene_name)){
                return scene_data;
        }
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
                FileIO::TryToRead(j_go.value(),"ObjectName",ErrorType::NO_ERROR,nullptr,&go->object_name);
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
                        bool is_main_cam = false;
                        if(FileIO::TryToRead(j_go.value(),"IsMainCamera", ErrorType::NO_ERROR,nullptr,&is_main_cam)){
                                Camera* camera;
                                //Checks if isMainCam true and if there was a camera created in the game object
                                if(is_main_cam && (camera = go->GetComponent<Camera>())){
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
        if(ComponentFactory::singleton->components_factories.find(j_component.get<std::string>()) == ComponentFactory::singleton->components_factories.end()){
                std::string params[] = {file_name,j_component.get<std::string>()};
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_NO_COMPONENT_FACTOR_FAIL,params);
                return nullptr;
        }
        //Returns from function factory
        return ComponentFactory::singleton->components_factories[j_component.get<std::string>()](j_values,file_name);
}