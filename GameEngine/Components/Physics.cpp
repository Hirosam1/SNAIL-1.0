#include "Components/Physics.hpp"

void Physics::Update(GameObject* game_object){
    velocity = velocity + acceleration * Time::deltaTime;
    game_object->transform->MovePos(Vector3(velocity) * Time::deltaTime);
}