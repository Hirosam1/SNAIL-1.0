#pragma once
#include "GameEngine.hpp"

class ObjectFollower : public Behaviour{
    public:
        float speed = .5f;
        GameObject* to_follow = nullptr;
        void Begin() override{
            for(Object* obj : Window::main_window->object_list){
                if(obj->object_name == "Main Camera"){
                    to_follow = dynamic_cast<GameObject*>(obj);
                }
            }
        }

        void Update() override{
            if(to_follow){
                Vector3 target = Normalize(to_follow->transform->Pos() - transform->Pos());
                transform->LookAt(target);
                //transform->AddRot(Vector3(0.0,2.0 * Time::deltaTime,0.0));
                transform->MovePos(target * speed * Time::deltaTime);
            }
        }
}; 