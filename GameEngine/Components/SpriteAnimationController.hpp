#pragma once


#include "Components/Component.hpp"
#include "Components/SpriteRenderer.hpp"

#include "GMpch.hpp"
#include "Debug.hpp"
#include "Time.hpp"
#include "Animation.hpp"


/*
This class handles the animaton of a SpriteRenderer.
The GameObject MUST have a sprite renderer with sprite atlas.
*/
class SpriteAnimationController : public Component{
    public:
        SpriteAnimationController(){};
        SpriteAnimationController(const SpriteAnimationController& cp);
        std::vector<Animation> animation_list;
        void Begin(GameObject* go) override;
        void Update(GameObject* go) override;

        void ChangeAnimation(int animation, bool restart_anim=false);
        int CurrentAnimationI();
        std::string CurrentAnimationS();
        void ChangeAnimation(const std::string& animation, bool restart_anim=false);
    private:
        SpriteRenderer* sprite_renderer;
        float timer=0;
        int current_animation =0;
        int current_key = 0;

};