#pragma once
#include "GameEngine.hpp"

class ObjectFollower : public Behaviour{
    public:
        float speed = .35f;
        GameObject* to_follow = nullptr;
        void Begin() override{
            to_follow = Scene::active_scene->FindGameObject("Main Camera");

            Renderer* renderer = game_object->GetComponent<Renderer>();
            Vector3 new_scale = renderer->mesh->texture->image_data.width > renderer->mesh->texture->image_data.height?
                                Vector3(renderer->mesh->texture->image_data.width/(float)renderer->mesh->texture->image_data.height,1.0,1.0) :
                                Vector3(1.0,renderer->mesh->texture->image_data.height/(float) renderer->mesh->texture->image_data.width,1.0);
            transform->SetScale(new_scale);
            obj_h_height = (float)transform->scale.y/2.0f;
        }

        void Update() override{
            if(to_follow){
                Vector3 target = to_follow->transform->Pos() - transform->Pos();
                if(Length(target) > 0.25f){
                    target = Normalize(target);
                    // transform->LookAt(to_follow->transform->position);
                    //Rotates only in the y axis
                    transform->rotation.y = atan2(target.x,target.z);
                    transform->Translate(target * speed * Time::deltaTime);
                    //Limit how far it can go down based on height
                    transform->position.y = Clamp(transform->position.y,obj_h_height,transform->position.y);
                }
            }
        }
        private:
            float obj_h_height;
}; 