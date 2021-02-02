#pragma once

class GameObject;

class Component {
    public:
        //Called when the behaviour component is created. And after all starting objects in the scene are created.
        virtual void Begin(GameObject* game_object){};
        virtual void Update(GameObject* game_object) = 0;
};