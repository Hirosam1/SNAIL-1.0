#include "CarController.hpp"
#include "CarFollower.hpp"

void CarController::Begin(){
    // physics_comp = game_object->GetComponent<Physics>();
    ih.AddCommandBack(GLFW_KEY_W,GLFW_PRESS,MOVE_FORWARDS);
    ih.AddCommandBack(GLFW_KEY_S,GLFW_PRESS,MOVE_BACKWARDS);
    ih.AddCommandBack(GLFW_KEY_A,GLFW_PRESS,TURN_LEFT);
    ih.AddCommandBack(GLFW_KEY_D,GLFW_PRESS,TURN_RIGHT);
}

void CarController::Update(){
    ih.HandleInput();
    // bool is_accel = false;
    // if(ih.GetInputInfo(MOVE_FORWARDS).was_activated){
    //     is_accel = true;
    //     physics_comp->acceleration = front_vector * accel;
    // }else if(ih.GetInputInfo(MOVE_BACKWARDS).was_activated){
    //     is_accel = true;
    //     physics_comp->acceleration = -front_vector * accel;
    // }else{
    //     physics_comp->acceleration = -physics_comp->velocity * deccel;
    // }
    
    // if(ih.GetInputInfo(TURN_LEFT).was_activated){
    //     float vel_lenght=  Length(physics_comp->velocity);
    //     float rot_amount = (ToRadians(150.0)*Time::deltaTime)/(vel_lenght+1.0f);
    //     game_object->transform->AddRot(Vector3(0,0, rot_amount));
    //     Vector2 vector_2d = Vector2(front_vector.x,front_vector.y).Rotate(rot_amount);
    //     front_vector = Vector3(vector_2d.x,vector_2d.y,front_vector.z);
    //     right_vector = front_vector.Cross(up_vector);
    //     physics_comp->acceleration = -right_vector * accel;
    // }
    // if(ih.GetInputInfo(TURN_RIGHT).was_activated){
    //     float vel_lenght=  Length(physics_comp->velocity);
    //     float rot_amount = -(ToRadians(150.0)*Time::deltaTime)/(vel_lenght+1.0f);
    //     game_object->transform->AddRot(Vector3(0,0, rot_amount));
    //     Vector2 vector_2d = Vector2(front_vector.x,front_vector.y).Rotate(rot_amount);
    //     front_vector = Vector3(vector_2d.x,vector_2d.y,front_vector.z);
    //     right_vector = front_vector.Cross(up_vector);
    //     physics_comp->acceleration = right_vector * accel;
    // }
            
}