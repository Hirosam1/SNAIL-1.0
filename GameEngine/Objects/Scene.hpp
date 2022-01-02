#pragma once
#include "GMpch.hpp"

#include "Objects/Object.hpp"
#include "Objects/GameObject.hpp"

#include "GLHandler/GLStateManager.hpp"

#include "Debug.hpp"

class Camera;
class GameObject;

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
        //Adds a resource object
        void AddObject(Object* object);
        //Finds a game object from the scene with the name
        GameObject* FindGameObject(const std::string& object_name);
        //Returns a list of the games objects of the scene
        std::list<GameObject*>& GameObjectList();
        //Load scene and unloads the current one, and set itself as the main scene
        static void LoadScene(const std::string& scene_path);
        //Unloads scene
        void UnloadScene();
        std::string scene_name;
        std::string scene_path;
    private:
        static Logger log;
        std::vector<Object*> objects;
        bool request_change = false;
        Scene* my_next_scene;
        std::list<GameObject*> game_objects;
};