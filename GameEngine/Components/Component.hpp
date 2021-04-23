#pragma once
#include "Objects/Object.hpp"

class GameObject;

class Component : public Object {
    public:
        GameObject* game_object = nullptr;
        //Called when the behaviour component is created. And after all starting objects in the scene are created.
        virtual void Begin(GameObject* game_object){}; 
        //Update method called once per frame by each component
        virtual void Update(GameObject* game_object) = 0;
};