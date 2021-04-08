#pragma once
#include "GameEngine.hpp"

class ObjectFollower : public Behaviour{
    public:
        float speed = .35f;
        GameObject* to_follow = nullptr;
        void Begin() override{
            for(Object* obj : Window::main_window->object_list){
                if(obj->object_name == "Main Camera"){
                    to_follow = dynamic_cast<GameObject*>(obj);
                }
            }
            Renderer* renderer = game_object->GetComponent<Renderer>();
            Vector3 new_scale = renderer->mesh->texture->image_data.width > renderer->mesh->texture->image_data.height?
                                Vector3(renderer->mesh->texture->image_data.width/(float)renderer->mesh->texture->image_data.height,1.0,1.0) :
                                Vector3(1.0,renderer->mesh->texture->image_data.height/(float) renderer->mesh->texture->image_data.width,1.0);
            transform->SetScale(new_scale);
        }

        void Update() override{
            if(to_follow){
                Vector3 target = to_follow->transform->Pos() - transform->Pos();
                if(Length(target) > 0.5f){
                    target = Normalize(target);
                    transform->LookAt(target);
                    transform->MovePos(target * speed * Time::deltaTime);
                }
            }
        }
}; 