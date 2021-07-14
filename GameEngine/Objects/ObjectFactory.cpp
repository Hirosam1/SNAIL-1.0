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
                {"Behavior", CreateBehavior}};
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
        std::string params[] = {file_name,"MeshRenderer"};
        if(FileIO::TryToRead(j,"Mesh",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&mesh_name)){
                mesh = ObjectsInfo::FindOrLoadMesh(mesh_name, game_objects);
        if(FileIO::TryToRead(j,"Shader", ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&shader_name)){
               shader = ResourcesInfo::FindOrLoadShader(shader_name, game_objects);
               if(mesh && shader){
                        m_r = new MeshRenderer(mesh,shader);
                        
                }else{
                     if(!shader){
                             params[1] = shader_name;
                             Debug::WriteErrorLog(ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,params);
                     }   
                     if(!mesh){
                             params[1] = mesh_name;  
                             Debug::WriteErrorLog(ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,params);
                     }
                }
        }
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
        std::string params[] = {file_name,"SpriteRenderer"};
        //Tries to get mesh
        if(!FileIO::TryToRead(j,"Mesh",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&obj_name)){
                return nullptr;
        }
        mesh = ObjectsInfo::FindOrLoadMesh(obj_name, game_objects);
        if(!mesh){
                params[1]  = obj_name;
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,params);
                return nullptr;
        }
        //Tries to get shader
        params[1] = "SpriteRenderer";
        if(!FileIO::TryToRead(j,"Shader",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&obj_name)){
                return nullptr;
        }
        shader = ResourcesInfo::FindOrLoadShader(obj_name, game_objects);
        if(!shader){
                params[1] = obj_name;
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,params);
                return nullptr;
        }
        //Tries to get sprite atlas
        if(FileIO::TryToRead(j,"SpriteAtlas",ErrorType::NO_ERROR,nullptr,&obj_name)){
                sprite_atlas = ObjectsInfo::FindOrLoadSpriteAtlas(obj_name, game_objects);
                if(!sprite_atlas){
                        params[1] = obj_name;
                        Debug::WriteErrorLog(ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,params);
                        return nullptr;  
                }
                params[1] = "SpriteRenderer";
                std::vector<int> vec2;
                if(!FileIO::TryToRead(j,"AtlasPosition",ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params,&vec2)){
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

Component* ComponentFactory::CreateCamera(json j, const std::string& file_name, std::vector<Object*>* game_objects){
        int i;
        if(!FileIO::TryToRead(j,"CameraProjection",ErrorType::NO_ERROR,nullptr,&i)){
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
        FileIO::TryToRead(j,"__THIS_CELL__",ErrorType::NO_ERROR,nullptr,&behavior_name);
        if(strcmp(behavior_name.data(),"CameraMovement") == 0){
                return dynamic_cast<Component*>(new CameraMovement());
        }else if(strcmp(behavior_name.data(),"HeadFollower") == 0){
                return dynamic_cast<Component*>(new HeadFollower());
        }else if(strcmp(behavior_name.data(),"MovingObject") == 0){
                return dynamic_cast<Component*>(new MovingObject());
        }else if(strcmp(behavior_name.data(),"ObjectFollower") == 0){
                return dynamic_cast<Component*>(new ObjectFollower());
        }else if(strcmp(behavior_name.data(),"RotateCubeQuat") == 0){
                return dynamic_cast<Component*>(new RotateCubeQuat());
        }
        std::string params[] = {file_name,behavior_name};
        Debug::WriteErrorLog(ErrorType::OBJECTLOADER_NO_BEHAVIOR_FAIL,params);
        return nullptr;

}

Transform ComponentFactory::CreateTransform(json j,const std::string& file_name){
        Transform trans = Transform();
        std::vector<float> vec3;
        if(FileIO::TryToRead(j,"Position",ErrorType::NO_ERROR,nullptr,&vec3)){
                if(vec3.size() == 3){
                        trans.position = Vector3(vec3[0],vec3[1],vec3[2]);
                }
        }
        if(FileIO::TryToRead(j,"Rotation",ErrorType::NO_ERROR,nullptr,&vec3)){
                if(vec3.size() == 3){
                        trans.SetRot(Vector3(vec3[0],vec3[1],vec3[2]));
                }
        }
        if(FileIO::TryToRead(j,"Scale",ErrorType::NO_ERROR,nullptr,&vec3)){
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
        if(!mesh){
                if(ObjectsInfo::singleton->meshes_map.find(name_ext) != ObjectsInfo::singleton->meshes_map.end()){
                        ObjectsInfo::MeshInfo mesh_i = ObjectsInfo::singleton->meshes_map[name_ext];
                        Model* model = ResourcesInfo::FindOrLoadModel(mesh_i.model_name, game_objects);
                        Texture* tex = ResourcesInfo::FindOrLoadTexture(mesh_i.texture_name, game_objects);
                        if(model && tex){
                                std::cout<< "Mesh -> " << name_ext << " created\n";
                                mesh = new Mesh(model,tex);
                                mesh->object_name = name_ext;
                                game_objects->push_back(mesh);
                                
                        }
                }
        }
        return mesh;
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
                                std::cout<< "SpriteAtlas -> " << name_ext << " created\n";
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
                        std::cout<< "Texture -> " << name_ext << " created\n";
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
                        std::cout<< "Shader -> " << name_ext << " created\n";
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
                                std::cout<< "Model  -> " << name_ext << " created\n";
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