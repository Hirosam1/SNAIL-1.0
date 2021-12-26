#include "GameEngine.hpp"



class CharacterMovement : public Behavior{
    public:
        enum{
            MOVE_UP,
            MOVE_DOWN,
            MOVE_LEFT,
            MOVE_RIGHT,
            ATTACK
        };
        GameObject* main_camera;
        float speed = 2.1;
        InputHandler ih = InputHandler(6);
        SpriteRenderer* sprite_rend;
        SpriteAnimationController* anim_ctr;
        //0-> Down 1->Right 2->Up 3->left
        int last_direction = 0;
        void Begin() override{
            main_camera = Scene::active_scene->FindGameObject("Main Camera");
            ih.AddCommandBack(GLFW_KEY_W,PressType::KEY_HOLD,MOVE_UP);
            ih.AddCommandBack(GLFW_KEY_S,PressType::KEY_HOLD,MOVE_DOWN);
            ih.AddCommandBack(GLFW_KEY_A,PressType::KEY_HOLD,MOVE_LEFT);
            ih.AddCommandBack(GLFW_KEY_D,PressType::KEY_HOLD,MOVE_RIGHT);
            ih.AddCommandBack(GLFW_KEY_E,PressType::KEY_PRESS,ATTACK);
            sprite_rend = game_object->GetComponent<SpriteRenderer>();
            anim_ctr = game_object->GetComponent<SpriteAnimationController>();

        }
        void EarlyUpdate() override{
            Vector3 mov_direction;
            bool moved = false;
            ih.HandleInput();
            if(ih.GetInputInfo(MOVE_UP).was_activated){
                mov_direction += Vector3(0.0,1.0,0.0);
                last_direction = 2;
                moved = true;
            }
            if(ih.GetInputInfo(MOVE_DOWN).was_activated){
                mov_direction -= Vector3(0.0,1.0,0.0);
                last_direction = 0;
                moved = true;
            }
            if(ih.GetInputInfo(MOVE_LEFT).was_activated){
                mov_direction -= Vector3(1.0,0.0,0.0);
                last_direction = 3;
                this->transform->SetScale(Vector3(-1.0,1.0,1.0));
                moved = true;
            }
            if(ih.GetInputInfo(MOVE_RIGHT).was_activated){
                mov_direction += Vector3(1.0,0.0,0.0);
                last_direction = 1;
                this->transform->SetScale(Vector3(1.0,1.0,1.0));
                moved = true;
            }
            if(moved){
                int anim = 0;
                switch (last_direction)
                {
                case 0:
                    anim = 1;
                    break;
                case 1:
                    anim = 3;
                    break;
                case 2:
                    anim = 5;
                    break;
                case 3:
                    anim = 3;
                    break;
                default:
                    break;
                }
                anim_ctr->ChangeAnimationI(anim);
            }else if(!moved){
                int anim = 0;
                switch (last_direction)
                {
                case 0:
                    anim = 0;
                    break;
                case 1:
                    anim = 2;
                    break;
                case 2:
                    anim = 4;
                    break;
                case 3:
                    anim = 2;
                    break;
                default:
                    break;
                }
                anim_ctr->ChangeAnimationI(anim);

            }

            Vector3 mov_final = Vector::Normalize(mov_direction)*speed*Time::deltaTime;
            this->transform->Translate(mov_final);
        }
};