#pragma once
#include "GMpch.hpp"
#include "Debug.hpp"
#include "Objects/ObjectFactory.hpp"

#include <json/json.hpp>

class GameObject;
class Camera;
class Component;

struct SceneData{
    std::string scene_name;
    std::list<GameObject*> game_objects;
    Camera* main_camera;
    void AddGameObject(GameObject* go){game_objects.push_back(go);};
};

namespace ObjectLoader {
        void LoadResources(const std::string& resources_path);
        SceneData LoadScene(const std::string& scene_path);
        Component* MakeComponent(nlohmann::json j_component, nlohmann::json j_values,const std::string& file_name);
};

namespace ObjectWriter{
    void WriteScene(SceneData scene_data);
}