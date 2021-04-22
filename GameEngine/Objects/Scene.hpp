#pragma once
#include "GMpch.hpp"
#include "Object.hpp"
#include "Objects/GameObject.hpp"

class Camera;
#include "SceneLoader.hpp"



class Scene : public Object{
    public:
        Scene() = default; 
        Scene(const std::string& scene_path);
        static Scene* active_scene;
        Camera* main_camera;
        //Starts a scene
        void BeginScene();
        //Does a one frame update
        void UpdateScene();
        //Adds a game object to the scene
        void AddGameObject(GameObject* game_object);
        //Finds a game object from the scene with the name
        GameObject* FindGameObject(const std::string& object_name);
        //Returns a list of the games objects of the scene
        std::list<GameObject*>& GameObjectList();
    private:
        std::list<GameObject*> game_objects;
};