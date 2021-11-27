#pragma once
#include "Objects/Object.hpp"

class GameObject;

class Component : public Object {
    public:
        GameObject* game_object = nullptr;
        //Called when the behaviour component is created. And after all starting objects in the scene are created.
        virtual void Begin(GameObject* game_object){}; 
        //Update method called once per frame by each component
        virtual void Update(GameObject* game_object){};
        //early update before update
        virtual void EarlyUpdate(GameObject* game_object){};
        //late update after update
        virtual void LateUpdate(GameObject* game_object){};
        //Methos caleed before deleting and ending component
        virtual void End(GameObject* game_object){};
};