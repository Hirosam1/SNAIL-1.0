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

Component* ComponentFactory::CreateSpriteRenderer(json j,const std::string& file_name){
        Mesh* mesh;
        Shader* shader;
        SpriteAtlas* sprite_atlas = nullptr;
        Vector2 atlas_pos;
        SpriteRenderer* sptr = nullptr;
        //Tries to get mesh
        if(!j.contains("Mesh")){
                std::string params[]{file_name,"SpriteRenderer"};
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params);
                return nullptr;   
        }
        mesh = dynamic_cast<Mesh*>(Object::FindObjectByName(j["Mesh"].get<std::string>()));
        if(!mesh){
                std::string params[]{file_name,j["Mesh"].get<std::string>()};
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,params);
                return nullptr;
        }
        //Tries to get shader
        if(!j.contains("Shader")){
                std::string params[]{file_name,"SpriteRenderer"};
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params);
                return nullptr; 
        }
        shader = dynamic_cast<Shader*>(Object::FindObjectByName(j["Shader"].get<std::string>()));
        if(!shader){
                std::string params[]{file_name,j["Shader"].get<std::string>()};
                Debug::WriteErrorLog(ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,params);
                return nullptr;
        }
        //Tries to get sprite atlas
        if(j.contains("SpriteAtlas")){
                sprite_atlas = dynamic_cast<SpriteAtlas*>(Object::FindObjectByName(j["SpriteAtlas"].get<std::string>()));
                if(!sprite_atlas){
                        std::string params[]{file_name,j["SpriteAtlas"].get<std::string>()};
                        Debug::WriteErrorLog(ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,params);
                        return nullptr;  
                }
                if(!j.contains("AtlasPosition")){
                        std::string params[]{file_name,"SpriteRenderer"};
                        Debug::WriteErrorLog(ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,params);
                        return nullptr;   
                }
                std::vector<int> vec2 = j["AtlasPosition"].get<std::vector<int>>();
                atlas_pos = Vector2(vec2[0],vec2[1]);
                //Create Sprite Renderer
                sptr = new SpriteRenderer(mesh,shader,sprite_atlas,atlas_pos.x,atlas_pos.y);
        }else{
                //Create Sprite Renderer
                sptr = new SpriteRenderer(mesh,shader); 
        }

        return dynamic_cast<Component*>(sptr);

}

Component* ComponentFactory::CreateCamera(json j, const std::string& file_name){
        if(!j.contains("CameraProjection")){
                return dynamic_cast<Component*>(new Camera());
        }
        int i = j["CameraProjection"].get<int>();
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

Component* ComponentFactory::CreateBehavior(json j, const std::string& file_name){
        std::string behavior_name = j.get<std::string>();
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
    if(j.size() == 1){
            std::vector<float> vec3 = j["Transform"].get<std::vector<float>>();
            if(vec3.size() == 3){
                trans.position = Vector3(vec3[0],vec3[1],vec3[2]);
            }
    }
    return trans;
}