#include "Objects/ObjectFactory.hpp"
//All includes but scene
#include "DataStructures/Vector.hpp"
#include "DataStructures/Matrix.hpp"
#include "DataStructures/ImplicitObjects.hpp"
#include "DataStructures/Quaternion.hpp"

#include "Math/Math.hpp"
#include "Math/Matrix_Transform.hpp"
#include "Math/Quternion_Transform.hpp"

#include "Objects/Object.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/SpriteAtlas.hpp"

#include "Components/Camera.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Renderer.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Components/Transform.hpp"
#include "Components/SpriteAnimationController.hpp"
#include "Components/BatchSpriteRenderer.hpp"

#include "Resources/Model.hpp"
#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"
//------------------------------------------
// Behaviour -------------------------------
#include "../MyFiles/include/Behaviors.hpp"

using namespace nlohmann;

ComponentFactory* ComponentFactory::singleton = nullptr;
ResourcesInfo* ResourcesInfo::singleton = nullptr;
ObjectsInfo* ObjectsInfo::singleton = nullptr;

const std::string ResourcesInfo::extension = "sres";
const std::string ObjectsInfo::extension = "sobj";

std::string ResourcesInfo::starting_scene_path = "NO SCENE";

Object* FindObjectByName(const std::string& obj_name, std::vector<Object*>* objects){
        for(Object* o : *objects){
        if(o){
            if(strcmp(o->object_name.data(),obj_name.data()) == 0){
                return o;
            }
        }
    }
    return nullptr;
}

ComponentFactory::ComponentFactory(){
        if(!singleton){
                components_factories = {      
                {"SpriteRenderer", CreateSpriteRenderer},
                {"MeshRenderer", CreateMeshRenderer},
                {"Camera", CreateCamera},
                {"Behavior", CreateBehavior},
                {"SpriteBatchRenderer", CreateSpriteBatchRenderer},
                {"SpriteAnimationController",CreateSpriteAnimationController}
                };
                singleton = this;
        }
        else{
                delete this;
        }
}

ResourcesInfo::ResourcesInfo(){
        if(!singleton){
                singleton = this;
        }else{
                delete this;
        }
}

ObjectsInfo::ObjectsInfo(){
        if(!singleton){
                singleton = this;
        }else{
                delete this;
        }
}

Component* ComponentFactory::CreateMeshRenderer(json j,const std::string& file_name, std::vector<Object*>* game_objects){
        MeshRenderer* m_r = nullptr;
        Mesh* mesh;
        Shader* shader;
        std::string shader_name;
        std::string mesh_name;
        bool success = false;
        if(FileIO::TryToRead(j,"Mesh",&mesh_name)){
                mesh = ObjectsInfo::FindOrLoadMesh(mesh_name, game_objects);
        if(FileIO::TryToRead(j,"Shader",&shader_name)){
               shader = ResourcesInfo::FindOrLoadShader(shader_name, game_objects);
               if(mesh && shader){
                        m_r = new MeshRenderer(mesh,shader);
                        success = true;
                        
                }else{
                     if(!shader){
                             ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" the object "+ shader_name +" created on resources does not exist, or does not match type.");
                     }   
                     if(!mesh){
                             ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" the object "+ mesh_name +" created on resources does not exist, or does not match type.");
                     }
                }
        }
        }
        if(!success){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component MeshRenderer" + ".");
        }
        return  m_r; 
}
// !! THIS CODE IS UGLY! REFACTOR IT  LIKE!!
Component* ComponentFactory::CreateSpriteRenderer(json j,const std::string& file_name, std::vector<Object*>* game_objects){
        Mesh* mesh;
        Shader* shader;
        SpriteAtlas* sprite_atlas = nullptr;
        Vector2 atlas_pos;
        SpriteRenderer* sptr = nullptr;
        std::string obj_name;
        //Tries to get mesh
        if(!FileIO::TryToRead(j,"Mesh",&obj_name)){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpriteRenderer. Missing Mesh.");
                return nullptr;
        }
        mesh = ObjectsInfo::FindOrLoadMesh(obj_name, game_objects);
        if(!mesh){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" the object "+ obj_name +" created on resources does not exist, or does not match type.");
                //OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL
                return nullptr;
        }
        //Tries to get shader
        if(!FileIO::TryToRead(j,"Shader",&obj_name)){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpriteRenderer. Missing Shader.");
                return nullptr;
        }
        shader = ResourcesInfo::FindOrLoadShader(obj_name, game_objects);
        if(!shader){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" the object "+ obj_name +" created on resources does not exist, or does not match type.");
                return nullptr;
        }
        //Tries to get sprite atlas
        if(FileIO::TryToRead(j,"SpriteAtlas",&obj_name)){
                sprite_atlas = ObjectsInfo::FindOrLoadSpriteAtlas(obj_name, game_objects);
                if(!sprite_atlas){
                        ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" the object "+ obj_name +" created on resources does not exist, or does not match type.");
                        return nullptr;  
                }
                std::vector<int> vec2;
                if(!FileIO::TryToRead(j,"AtlasPosition",&vec2)){
                        ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpriteRenderer. Missing AtlasPosition.");
                        return nullptr;
                }
                atlas_pos = Vector2(vec2[0],vec2[1]);
                //Create Sprite Renderer
                sptr = new SpriteRenderer(mesh,shader,sprite_atlas,atlas_pos.x,atlas_pos.y);
        }else{
                //Create Sprite Renderer
                sptr = new SpriteRenderer(mesh,shader); 
        }

        return dynamic_cast<Component*>(sptr);

}

Component* ComponentFactory::CreateSpriteAnimationController(nlohmann::json j,const std::string& file_name, std::vector<Object*>* game_objects){
        std::string obj_name;
        if(!FileIO::TryToRead(j,"Controller",&obj_name)){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpriteAnimationController. Missing Controller.");
                return nullptr;
        }
        SpriteAnimationController* prime_sac = ObjectsInfo::FindOrLoadSpriteAnimationController(obj_name,game_objects);
        if(!prime_sac){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" the object "+ obj_name +" created on resources does not exist, or does not match type.");
                return nullptr;
        }
        SpriteAnimationController* sac = new SpriteAnimationController(*prime_sac);
        return dynamic_cast<Component*>(sac);

}

Component* ComponentFactory::CreateSpriteBatchRenderer(nlohmann::json j,const std::string& file_name, std::vector<Object*>* game_objects){
        BatchSpriteRenderer* batch_rend = nullptr;
        SpriteAtlas* sprite_atlas = nullptr;
        Shader* shader = nullptr;
        std::string obj_name;

        if(!FileIO::TryToRead(j,"SpriteAtlas",&obj_name)){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpritebatchRenderer. Missing SpriteAtlas.");
                return nullptr;  
        }
        sprite_atlas = ObjectsInfo::FindOrLoadSpriteAtlas(obj_name,game_objects);
        if(!sprite_atlas){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" the object "+ obj_name +" created on resources does not exist, or does not match type.");
                return nullptr;  
        }
        if(!FileIO::TryToRead(j,"Shader",&obj_name)){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpritebatchRenderer. Missing Shader.");
                return nullptr;  
        }

        shader = ResourcesInfo::FindOrLoadShader(obj_name,game_objects);
        if(!shader){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" the object "+ obj_name +" created on resources does not exist, or does not match type.");
                return nullptr;  
        }
        if(!j.contains("SpriteInstances")){
                ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpritebatchRenderer. Missing SpriteInstances.");
                return nullptr;  
        }
        batch_rend = new BatchSpriteRenderer(sprite_atlas,shader);
        json j_si = j["SpriteInstances"];
        for(json::iterator j_instances = j_si.begin() ; j_instances != j_si.end(); j_instances++){
                std::vector<float> pos;
                std::vector<float>atlas_pos;
                json j_instances_v = j_instances.value();
                if(!FileIO::TryToRead(j_instances_v,"Position",&pos)){
                        ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpritebatchRenderer. Missing Position.");
                        return nullptr;
                }

                if(!FileIO::TryToRead(j_instances_v,"AtlasPosition",&atlas_pos)){
                        ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpritebatchRenderer. Missing AtlasPosition.");
                        return nullptr;
                }
                if(pos.size() != 3 || atlas_pos.size() != 2){
                        ComponentFactory::singleton->log.LogError("From the scene "+ file_name +" is passing bad/few paramters to component SpriteInstances. Invalid vector size on Position.");

                }else{
                        batch_rend->AddSprite(Vector3(pos[0],pos[1],pos[2]), 0, Vector2(atlas_pos[0],atlas_pos[1]));
                }

        }
        batch_rend->GenerateGeometry();
        return dynamic_cast<Component*>(batch_rend);

}

Component* ComponentFactory::CreateCamera(json j, const std::string& file_name, std::vector<Object*>* game_objects){
        int i;
        if(!FileIO::TryToRead(j,"CameraProjection",&i)){
                return dynamic_cast<Component*>(new Camera());
        }
        switch (i)
        {
        case 0:
                return dynamic_cast<Component*>(new Camera(Camera_Projection::ORTHOGRAPHIC_PROJECTION));
        case 1:
                return dynamic_cast<Component*>(new Camera(Camera_Projection::PERSPECTIVE_PROJECTION));
        
        default:
                return nullptr;
        }
}

Component* ComponentFactory::CreateBehavior(json j, const std::string& file_name, std::vector<Object*>* game_objects){
        // std::string behavior_name = j.get<std::string>();
        std::string behavior_name;
        FileIO::TryToRead(j,"__THIS_CELL__",&behavior_name);
        if(strcmp(behavior_name.data(),"CameraMovement") == 0){
                return dynamic_cast<Component*>(new CameraMovement());
        }else if(strcmp(behavior_name.data(),"MovingObject") == 0){
                return dynamic_cast<Component*>(new MovingObject());
        }else if(strcmp(behavior_name.data(),"ObjectFollower") == 0){
                return dynamic_cast<Component*>(new ObjectFollower());
        }else if(strcmp(behavior_name.data(),"RotateCubeQuat") == 0){
                return dynamic_cast<Component*>(new RotateCubeQuat());
        }else if(strcmp(behavior_name.data(),"CharacterMovement")==0){
                return dynamic_cast<Component*>(new CharacterMovement());
        }else if(strcmp(behavior_name.data(),"FollowObject")==0){
                return dynamic_cast<Component*>(new FollowObject());
        }else if(strcmp(behavior_name.data(),"EnemyMovement")==0){
                return dynamic_cast<Component*>(new EnemyMovement());
        }
        ComponentFactory::singleton->log.LogError("From the scene" + file_name +" there is no behavior named "+ behavior_name +".");
        return nullptr;

}

Transform ComponentFactory::CreateTransform(json j,const std::string& file_name){
        Transform trans = Transform();
        std::vector<float> vec3;
        if(FileIO::TryToRead(j,"Position",&vec3)){
                if(vec3.size() == 3){
                        trans.position = Vector3(vec3[0],vec3[1],vec3[2]);
                }
        }
        if(FileIO::TryToRead(j,"Rotation",&vec3)){
                if(vec3.size() == 3){
                        trans.SetRot(Vector3(vec3[0],vec3[1],vec3[2]));
                }
        }
        if(FileIO::TryToRead(j,"Scale",&vec3)){
                if(vec3.size() == 3){
                        trans.scale = Vector3(vec3[0],vec3[1],vec3[2]);
                }
        }
        return trans;
}


Mesh* ObjectsInfo::FindOrLoadMesh(const std::string& name, std::vector<Object*>* game_objects){
        std::string name_ext = name + "." + ObjectsInfo::extension;
        //Tries to find if the object's already loaded on scene
        Mesh* mesh = dynamic_cast<Mesh*>(FindObjectByName(name_ext, game_objects));
        Texture* tex;
        bool tex_good = false;
        if(!mesh){
                if(ObjectsInfo::singleton->meshes_map.find(name_ext) != ObjectsInfo::singleton->meshes_map.end()){
                        ObjectsInfo::MeshInfo mesh_i = ObjectsInfo::singleton->meshes_map[name_ext];
                        Model* model = ResourcesInfo::FindOrLoadModel(mesh_i.model_name, game_objects);
                        if(strcmp(mesh_i.texture_name.data(),"__NO_TEXTURE__") == 0){
                                tex = nullptr;
                                tex_good = true;
                        }
                        else{
                                tex = ResourcesInfo::FindOrLoadTexture(mesh_i.texture_name, game_objects);
                                if(tex){
                                        tex_good = true;
                                }
                        }
                        if(model && tex_good){
                                //std::cout<< "Mesh -> " << name_ext << " created\n";
                                mesh = new Mesh(model,tex);
                                mesh->object_name = name_ext;
                                game_objects->push_back(mesh);
                                
                        }
                }
        }
        return mesh;
}


SpriteAnimationController* ObjectsInfo::FindOrLoadSpriteAnimationController(const std::string& name, std::vector<Object*>* game_objects){
        std::string name_ext = name + "." + ObjectsInfo::extension;
        SpriteAnimationController* sac = dynamic_cast<SpriteAnimationController*>(FindObjectByName(name_ext,game_objects));
        if(!sac){
                if(ObjectsInfo::singleton->sac_map.find(name_ext) != ObjectsInfo::singleton->sac_map.end()){
                        ObjectsInfo::SpriteAnimationControllerInfo sac_info = ObjectsInfo::singleton->sac_map[name_ext];
                        sac = new SpriteAnimationController();
                        for(int i = 0; i < sac_info.animations.size(); i++){
                                sac->animation_list.push_back(sac_info.animations[i]);
                        }
                        sac->object_name= name_ext;
                        game_objects->push_back(sac);
                }
        }
        return sac;
}

SpriteAtlas* ObjectsInfo::FindOrLoadSpriteAtlas(const std::string& name, std::vector<Object*>* game_objects){
        std::string name_ext = name + "." + ObjectsInfo::extension;
        //Tries to find if the object's already loaded on scene
        SpriteAtlas* atlas = dynamic_cast<SpriteAtlas*>(FindObjectByName(name_ext,game_objects));
        if(!atlas){
                if(ObjectsInfo::singleton->sprite_atlas_map.find(name_ext) != ObjectsInfo::singleton->sprite_atlas_map.end()){
                        ObjectsInfo::SpriteAtlasInfo s_info = ObjectsInfo::singleton->sprite_atlas_map[name_ext];
                        Texture* tex = ResourcesInfo::FindOrLoadTexture(s_info.sheet_texture_name, game_objects);
                        if(tex){
                                //std::cout<< "SpriteAtlas -> " << name_ext << " created\n";
                                atlas = new SpriteAtlas(tex, s_info.atlas_dimensions.x, s_info.atlas_dimensions.y);
                                atlas->object_name = name_ext;
                                game_objects->push_back(atlas);
                        }
                }
        }
        return atlas;
}

Texture* ResourcesInfo::FindOrLoadTexture(const std::string& name, std::vector<Object*>* game_objects){
        std::string name_ext = name + "." + ResourcesInfo::extension;
        //Tries to find if the object's already loaded on scene
        Texture* tex = dynamic_cast<Texture*>(FindObjectByName(name_ext, game_objects));
        if(!tex){
                if(ResourcesInfo::singleton->texture_map.find(name_ext) != ResourcesInfo::singleton->texture_map.end()){
                        //sstd::cout<< "Texture -> " << name_ext << " created\n";
                        tex = new Texture(ResourcesInfo::singleton->texture_map[name_ext].texture_path);
                        tex->object_name = name_ext;
                        game_objects->push_back(tex);
                }
        }
        return tex;
}

Shader* ResourcesInfo::FindOrLoadShader(const std::string& name, std::vector<Object*>* game_objects){
        std::string name_ext = name + "." + ResourcesInfo::extension;
        //Tries to find if the object's already loaded on scene
        Shader* shader=  dynamic_cast<Shader*>(FindObjectByName(name_ext, game_objects));
        if(!shader){
                if(ResourcesInfo::singleton->shaders_map.find(name_ext) != ResourcesInfo::singleton->shaders_map.end()){
                        //std::cout<< "Shader -> " << name_ext << " created\n";
                        shader = new Shader(ResourcesInfo::singleton->shaders_map[name_ext].vertex_path,ResourcesInfo::singleton->shaders_map[name_ext].fragment_path);
                        shader->object_name = name_ext;
                        game_objects->push_back(shader);
                }
        }
        return shader;
}

Model* ResourcesInfo::FindOrLoadModel(const std::string& name, std::vector<Object*>* game_objects){
        std::string name_ext = name + "." + ResourcesInfo::extension;
        //Tries to find if the object's already loaded on scene
        Model* model = dynamic_cast<Model*>(FindObjectByName(name_ext, game_objects));
        if(!model){
                if(ResourcesInfo::singleton->model_map.find(name_ext) != ResourcesInfo::singleton->model_map.end()){
                        if(ResourcesInfo::singleton->model_map[name_ext].default_shape >= 0){
                                //std::cout<< "Model  -> " << name_ext << " created\n";
                                switch (ResourcesInfo::singleton->model_map[name_ext].default_shape)
                                {
                                case 0:
                                        model = new Model(DefaultShapes::SquareWithTex());
                                        model->object_name = name_ext;
                                        game_objects->push_back(model);
                                        break;
                                case 1:
                                        model = new Model(DefaultShapes::CubeWithTex());
                                        model->object_name = name_ext;
                                        game_objects->push_back(model);
                                        break;
                                
                                default:
                                        break;
                                }
                                
                        }
                }
        }
        return model;
}