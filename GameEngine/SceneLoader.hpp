#pragma once
#include "GMpch.hpp"

class GameObject;
class Camera;

struct SceneData{
    std::list<GameObject*> game_objects;
    Camera* main_camera;
    void AddGameObject(GameObject* go){game_objects.push_back(go);};
};

class SceneLoader {
    public:
        static void LoadResources(const std::string& resources_path);
        static SceneData LoadScene(const std::string& scene_path);
};