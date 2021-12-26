#include "GameEngine.hpp"



class EnemyMovement : public Behavior{
    GameObject* character;
    float speed =1.0f;
    void Begin() override{
        character = Scene::active_scene->FindGameObject("character");
    }

    void Update() override{
        Vector3 direction = character->transform->position - transform->position;
        if(Vector::Length(direction) > .5){
            direction = Vector::Normalize(Vector3(direction.x,direction.y,0));
            transform->Translate(direction*speed*Time::deltaTime);
        }
    }
};