#include "Components/SpriteAnimationController.hpp"

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

void SpriteAnimationController::ChangeAnimationI(int anim,bool restart_anim){
    if(!restart_anim && this->current_animation == anim){
        return;
    }
    if(anim >= animation_list.size()){
        return;
    }
    timer = 0;
    current_key = 0;
    sprite_renderer->SetAtlasCoordinate(animation_list[anim].animation_keys[0].atlas_pos);
    current_animation = anim;
}

int SpriteAnimationController::CurrentAnimationI(){
    return current_animation;
}