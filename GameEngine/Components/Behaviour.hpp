#pragma once
#include "Components/Component.hpp"
#include "Window.hpp"

class GameObject;
//Maybe make a LuaBehaviour later :)
class Behaviour : public Component{
    public:
        Window* main_window;
        Transform* transform;
        void Begin(GameObject* _game_object) override{this->game_object = _game_object;main_window = Window::main_window;transform = _game_object->transform;Begin();};
        //Called each frame
        void Update(GameObject* _game_object) override {Update();};

        virtual void Begin(){};
        virtual void Update()= 0;
        
};