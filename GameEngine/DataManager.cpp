#include "DataManager.hpp"
//All includes but scene
#include "Objects/GameObject.hpp"

#include "Components/Camera.hpp"

using namespace nlohmann;

Logger ObjectLoader::log = Logger("ObjectLoader");

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
                std::cout<< "Failed to load resource file!!\n";
                #endif
                ObjectLoader::log.LogError("Failed to load the " + resources_path +" file, check the name/extension.");
                return;
        } 
        json j;
        i_f >> j;
        if(!j.contains("ResourceInfo")){
                ObjectLoader::log.LogError("There is not enough information in resource file " + resources_path + "Missing(ResourceInfo).");
                return;
        }
        if(!j["ResourceInfo"].contains("ResourceName")){
                ObjectLoader::log.LogError("There is not enough information in resource file " + resources_path + "Missing(ResourceName).");
                return;
        }
        
        if(!FileIO::TryToRead(j["ResourceInfo"],"StartingScene",&ResourcesInfo::starting_scene_path)){
                std::cout<<"No scene\n";
        }else{
                ObjectLoader::log.LogError("There is not enough information in resource file " + resources_path + "Missing(StartingScene).");
        }

        if(j.contains("ResourceData")){
                json j_aux = j["ResourceData"];
                if(j_aux.contains("Shaders")){
                        //Get all shaders
                        for(json::iterator j_sh = j_aux["Shaders"].begin() ; j_sh != j_aux["Shaders"].end() ; j_sh++){
                                ResourcesInfo::ShaderInfo shader_info;
                                std::string shader_name;
                                std::string params[] = {resources_path,"Shader"};
                                bool success = false;
                                if(FileIO::TryToRead(j_sh.value(),"Name",&shader_name)){
                                if(FileIO::TryToRead(j_sh.value(),"VertexPath",&shader_info.vertex_path)){
                                if(FileIO::TryToRead(j_sh.value(),"FragmentPath",&shader_info.fragment_path)){
                                        shader_name = shader_name + "." + ResourcesInfo::extension;    
                                        ResourcesInfo::singleton->shaders_map[shader_name] = shader_info;
                                        success = true;
                                }
                                if(!success){
                                ObjectLoader::log.LogError("From the scene "+ resources_path +" is passing bad/few paramters to component Models of Name="+ shader_name + ".");
                                }
                                }else{
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" component of type SpriteAtlas is missing parameter Name" + ".");
                                }
                                }
                                if(!success){
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" is passing bad/few paramters to component Shader" + ".");
                                }
                        }
                }
                if(j_aux.contains("Textures")){
                        std::string params[] = {resources_path,"Textures"};
                        std::string texture_name;
                        ResourcesInfo::TextureInfo tex_info;
                        bool success = false;
                        for(json::iterator j_tex = j_aux["Textures"].begin() ; j_tex != j_aux["Textures"].end() ; j_tex++){
                        if(FileIO::TryToRead(j_tex.value(),"Name",&texture_name)){
                        if(FileIO::TryToRead(j_tex.value(),"TexturePath",&tex_info.texture_path)){
                                texture_name = texture_name + "." + ResourcesInfo::extension;
                                ResourcesInfo::singleton->texture_map[texture_name] = tex_info;
                                success = true;
                        }
                        if(!success){
                                ObjectLoader::log.LogError("From the scene "+ resources_path +" is passing bad/few paramters to component Models of Name="+ texture_name + ".");
                        }
                        }else{
                                ObjectLoader::log.LogError("From the scene "+ resources_path +" component of type SpriteAtlas is missing parameter Name" + ".");
                        }
                        }
                        if(!success){
                                ObjectLoader::log.LogError("From the scene "+ resources_path +" is passing bad/few paramters to component Textures" + ".");
                        }
                }
                if(j_aux.contains("Models")){
                        std::string params[] = {resources_path,"Models"};
                        std::string model_name;
                        ResourcesInfo::ModelInfo model_info;
                        bool success = false;
                        for(json::iterator j_model = j_aux["Models"].begin() ; j_model != j_aux["Models"].end() ; j_model++){
                                if(FileIO::TryToRead(j_model.value(),"Name",&model_name)){
                                int i;
                                if(FileIO::TryToRead(j_model.value(),"DefaultShape",&i)){
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
                                        success = true;
                                        model_name = model_name + "." + ResourcesInfo::extension;
                                        ResourcesInfo::singleton->model_map[model_name] = model_info;
                                }
                                if(!success){
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" is passing bad/few paramters to component Models" + ".");
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
                                bool success = false;
                                if(FileIO::TryToRead(j_spa.value(),"Name",&atlas_name)){
                                if(FileIO::TryToRead(j_spa.value(),"SheetTexture",&atlas_info.sheet_texture_name)){
                                if(FileIO::TryToRead(j_spa.value(),"SheetDimensions",&vec2)){
                                        atlas_info.atlas_dimensions = Vector2(vec2[0],vec2[1]);
                                        atlas_name = atlas_name + "." + ObjectsInfo::extension;
                                        success = true;
                                        ObjectsInfo::singleton->sprite_atlas_map[atlas_name] = atlas_info;
                                }
                                }
                                if(!success){
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" is passing bad/few paramters to component Models of Name="+ atlas_name + ".");
                                }
                                }else{
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" component of type SpriteAtlas is missing parameter Name" + ".");
                                }
                        }
                }
                if(j_aux.contains("AnimationControllers")){
                     std::string params[] = {resources_path,"AnimationControllers"};
                     for(json::iterator j_spa = j_aux["AnimationControllers"].begin() ; j_spa != j_aux["AnimationControllers"].end() ; j_spa++){
                        std::string sac_name;
                        ObjectsInfo::SpriteAnimationControllerInfo sac_info;
                        bool success = false;
                        if(FileIO::TryToRead(j_spa.value(),"Name",&sac_name)){
                                json animations = j_spa.value()["Animations"].get<json>();
                                for(json::iterator j_anim = animations.begin() ; j_anim != animations.end() ; j_anim++){
                                        Animation anim;
                                                if(j_anim.value().contains("AnimationKeys")){
                                                if(FileIO::TryToRead(j_anim.value(),"Name",&anim.name)){
                                                        for(json::iterator j_key_f = j_anim.value()["AnimationKeys"].begin(); j_key_f != j_anim.value()["AnimationKeys"].end(); j_key_f++){
                                                                float time_to_wait;
                                                                std::vector<int> atlas_pos;
                                                                if(FileIO::TryToRead(j_key_f.value(),"WaitTime",&time_to_wait)){
                                                                if(FileIO::TryToRead(j_key_f.value(),"AtlasPos",&atlas_pos)){
                                                                if(atlas_pos.size() == 2){
                                                                        anim.animation_keys.push_back({time_to_wait,Vector2(atlas_pos[0],atlas_pos[1])});
                                                                }
                                                                }
                                                                }
                                                        }
                                                }
           
                                        }
                                        sac_info.animations.push_back(anim);
                                }
                                if(!success){
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" is passing bad/few paramters to component AnimationControllers of Name="+ sac_name + ".");
                                }
                                }else{
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" component of type AnimationControllers is missing parameter Name" + ".");
                                }
                        sac_name = sac_name + "." + ObjectsInfo::extension;
                        ObjectsInfo::singleton->sac_map[sac_name] = sac_info;
                     }          
                }
                if(j_aux.contains("Meshes")){
                        std::string params[] = {resources_path,"Meshes"};
                        for(json::iterator j_m = j_aux["Meshes"].begin() ; j_m != j_aux["Meshes"].end() ; j_m++){
                                std::string mesh_name;
                                ObjectsInfo::MeshInfo mesh_info;
                                bool success = true;
                                if(FileIO::TryToRead(j_m.value(),"Name",&mesh_name)){
                                if(FileIO::TryToRead(j_m.value(),"Model",&mesh_info.model_name)){
                                if(!FileIO::TryToRead(j_m.value(),"Texture",&mesh_info.texture_name)){
                                        mesh_info.texture_name = "__NO_TEXTURE__";
                                }
                                        mesh_name = mesh_name + "." + ObjectsInfo::extension;
                                        ObjectsInfo::singleton->meshes_map[mesh_name] = mesh_info;
                                }
                                if(!success){
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" is passing bad/few paramters to component Meshes of Name="+ mesh_name + ".");
                                }
                                }else{
                                        ObjectLoader::log.LogError("From the scene "+ resources_path +" component of type Meshes is missing parameter Name" + ".");
                                }

                        }
                }
        }

}

SceneData ObjectLoader::LoadScene(const std::string& scene_path){
        std::ifstream i_f(scene_path);
        #ifdef DEBUG
        std::cout<<"Loading scene: " << scene_path << "\n";
        #endif
        //Checks if the file exists
        if(!i_f){
                #ifdef DEBUG
                std::cout<< "Failed to load scene file!\n";
                #endif
                ObjectLoader::log.LogError("Failed to load the " + scene_path + " file, check the name/extension.");
                return SceneData{};
        }
        //Loads file into program
        SceneData scene_data;
        json j;
        i_f >> j;
        if(!j.contains("SceneInfo")){
                ObjectLoader::log.LogError("There is not enough scene information in file " + scene_path + " scene must have: SceneInfo.");
                return scene_data;
        }
        if(!FileIO::TryToRead(j["SceneInfo"],"SceneName",&scene_data.scene_name)){
                ObjectLoader::log.LogError("There is not enough scene information in file " + scene_path + " scene must have: SceneName.");
                return scene_data;
        }
        //Checks if there is data in scene
        if(!j.contains("SceneData")){
                ObjectLoader::log.LogWarning("Scene " + scene_path + " is completely empty!");
                return scene_data;
        }
        json j_game_objects = j["SceneData"];
        if(!j_game_objects.contains("GameObjects")){
                ObjectLoader::log.LogWarning("Scene " + scene_path + " is completely empty!");
                return scene_data;
        }
        j_game_objects = j_game_objects["GameObjects"];
        for(json::iterator j_go = j_game_objects.begin(); j_go != j_game_objects.end(); j_go++){
                GameObject* go = new GameObject();
                FileIO::TryToRead(j_go.value(),"ObjectName",&go->object_name);
                if(j_go.value().contains("ObjectComponents")){
                        json j_go_comps = j_go.value()["ObjectComponents"];
                        for(json::iterator j_comp = j_go_comps.begin() ; j_comp != j_go_comps.end() ; j_comp++){
                                json::object_t obj = j_comp.value().get<json::object_t>();
                                if(strcmp(obj.begin()->first.data(),"Transform") == 0){
                                        *go->transform = ComponentFactory::CreateTransform(obj.begin()->second,scene_path);
                                }
                                else{
                                        Component* comp = MakeComponent(obj.begin()->first, obj.begin()->second, scene_path, &scene_data);
                                        
                                        if(comp){
                                                go->PushComponentBack(comp);
                                        }
                                }

                        }
                }
                if(j_go.value().contains("IsMainCamera")){
                        bool is_main_cam = false;
                        if(FileIO::TryToRead(j_go.value(),"IsMainCamera",&is_main_cam)){
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


Component* ObjectLoader::MakeComponent(json j_component, json j_values,const std::string& file_name, SceneData* scene_data){
        //Checks if component factory exists
        if(ComponentFactory::singleton->components_factories.find(j_component.get<std::string>()) == ComponentFactory::singleton->components_factories.end()){
                std::string params[] = {file_name,j_component.get<std::string>()};
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_NO_COMPONENT_FACTOR_FAIL,params);
                return nullptr;
        }
        //Returns from function factory
        return ComponentFactory::singleton->components_factories[j_component.get<std::string>()](j_values,file_name, &scene_data->objects);
}