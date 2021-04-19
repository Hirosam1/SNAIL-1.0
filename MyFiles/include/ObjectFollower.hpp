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
            transform->position = Vector3(transform->position.x,obj_h_height,transform->position.z);
        }

        void Update() override{
            if(to_follow){
                Vector3 target = Vector3(to_follow->transform->Pos().x,0.0,to_follow->transform->Pos().z) - Vector3(transform->Pos().x,0.0,transform->Pos().z);
                if(Vector::Length(target) > 0.20f){
                    target = Vector::Normalize(target);
                    // transform->LookAt(to_follow->transform->position);
                    //Rotates only in the y axis
                    transform->SetRot(Vector3(0.0f,atan2(target.x,target.z),0.0f));
                    transform->Translate(target * speed * Time::deltaTime);
                    //Limit how far it can go down based on height
                    // transform->position.y = Math::Clamp(transform->position.y,,transform->position.y);
                }
            }
        }
        private:
            float obj_h_height;
}; 