#include "Components/SpriteAnimationController.hpp"


SpriteAnimationController::SpriteAnimationController(const SpriteAnimationController& cp){
    this->animation_list = cp.animation_list;
    this->object_name = cp.object_name;
}


void SpriteAnimationController::Begin(GameObject* game_object){
    sprite_renderer = game_object->GetComponent<SpriteRenderer>();
    if(sprite_renderer == nullptr){
        std::cout<<"Couldn't find sprite renderer on game object " << game_object->object_name <<".\n";
    }
}


void SpriteAnimationController::Update(GameObject* game_object){
    timer+=Time::deltaTime;
    if(timer >= animation_list[current_animation].animation_keys[current_key].wait_time){
        timer = 0;
        current_key++;
        if(current_key == animation_list[current_animation].animation_keys.size()){
            current_key = 0;
        }
        sprite_renderer->SetAtlasCoordinate(animation_list[current_animation].animation_keys[current_key].atlas_pos);
    }
}

void SpriteAnimationController::ChangeAnimation(int animation,bool restart_anim){
    if(!restart_anim && this->current_animation == animation){
        return;
    }
    if(animation >= animation_list.size()){
        return;
    }
    timer = 0;
    current_key = 0;
    sprite_renderer->SetAtlasCoordinate(animation_list[animation].animation_keys[0].atlas_pos);
    current_animation = animation;
}

void SpriteAnimationController::ChangeAnimation(const std::string& animation, bool restart_anim){
    int anim = -1;
    for(int i =  0; i < animation_list.size(); i++){
        if(strcmp(animation_list[i].name.data(),animation.data()) == 0){
            anim = i;
            break;
        }
    }
    if(anim == -1){
        return;
    }
    this->ChangeAnimation(anim);
}

std::string SpriteAnimationController::CurrentAnimationS(){
    return animation_list[current_animation].name;
}

int SpriteAnimationController::CurrentAnimationI(){
    return current_animation;
}