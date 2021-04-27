#pragma once
#include "GameEngine.hpp"

class ObjectFollower : public Behavior{
    public:
        float speed = .35f;
        GameObject* to_follow = nullptr;
        void Begin() override{
            // to_follow = Scene::active_scene->FindGameObject("Main Camera");

            to_follow = Scene::active_scene->main_camera->game_object;

            obj_h_height = (game_object->GetComponent<SpriteRenderer>()->SpriteScale().y *  transform->scale.y)/2.0f;
            transform->position = Vector3(transform->position.x,obj_h_height,transform->position.z);
        }

        void Update() override{
            if(to_follow){
                Vector3 target = Vector3(to_follow->transform->Pos().x,0.0,to_follow->transform->Pos().z) - Vector3(transform->Pos().x,0.0,transform->Pos().z);
                if(Vector::Length(target) > 0.20f){
                    target = Vector::Normalize(target);
                    transform->SetRot(Vector3(0.0f,atan2(target.x,target.z),0.0f));
                    transform->Translate(target * speed * Time::deltaTime);
                }
            }
        }
        private:
            float obj_h_height;
}; 