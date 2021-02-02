#pragma once
#include "Components/Component.hpp"

class GameObject;
//Maybe make a LuaBehaviour later :)
class Behaviour : public Component{
    public:
        GameObject* game_object;
        void Begin(GameObject* _game_object){this->game_object = _game_object;Begin();};
        //Called each frame
        void Update(GameObject* _game_object){Update();};

        virtual void Begin(){};
        virtual void Update()= 0;
        
};