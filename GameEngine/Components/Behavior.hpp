#pragma once
#include "Components/Component.hpp"

#include "Window.hpp"

#include "Objects/GameObject.hpp"

//Maybe make a LuaBehaviour later :)
class Behavior : public Component{
    public:
        Transform* transform;
        void Begin(GameObject* _game_object) override{this->game_object = _game_object;transform = _game_object->transform;Begin();};
        //Called each frame
        void Update(GameObject* _game_object) override {Update();};

        virtual void Begin(){};
        virtual void Update()= 0;
        
};