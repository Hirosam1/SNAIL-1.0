#include "CarFollower.hpp"
#include "CarController.hpp"


void CarFollower::Update(){
    if(car){
        Vector3 direction = car->transform->Pos() - game_object->transform->Pos();
        if(Length(direction) >  0.9){
           // game_object->transform->MovePos(Normalize(direction)* Time::deltaTime * velocity);
        }
    }
        
}
void CarFollower::Begin(){
    for(Object* go : Window::main_window->object_list){
        if(go->object_name == "Car"){
            car = dynamic_cast<GameObject*>(go);
        }
    }
}