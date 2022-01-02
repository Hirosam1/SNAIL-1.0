#pragma once
#include "GMpch.hpp"
#include "Debug.hpp"
#include "Objects/ObjectFactory.hpp"
#include "Objects/Object.hpp"
#include "Components/Transform.hpp"
#include "FileIO.hpp"

#include "ResourcesMetaData.hpp"

#include <json/json.hpp>

class GameObject;
class Camera;
class Component;

struct SceneData{
    std::string scene_name;
    std::list<GameObject*> game_objects;
    Camera* main_camera;
    std::vector<Object*> objects = std::vector<Object*>();
    void AddGameObject(GameObject* go){game_objects.push_back(go);};
};

namespace ObjectLoader {
        //Reads Resources file, and build meta-data for the source files, that will be used in the scene loading, the game will save names of objects and file paths
        //to be used in the scene loading when they are used
        void LoadResources(const std::string& resources_path);
        //Reads and loads objects based on the resource data, it will create the game objects and bind with the components in it, using the objectFactory file.
        SceneData LoadScene(const std::string& scene_path);
        Component* MakeComponent(nlohmann::json j_component, nlohmann::json j_values,const std::string& file_name, SceneData* scene_data);
        static Logger log;
};

 

namespace ObjectWriter{
    void WriteScene(SceneData scene_data);
}