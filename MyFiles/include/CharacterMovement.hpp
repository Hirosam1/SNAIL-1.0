#include "GameEngine.hpp"



class CharacterMovement : public Behavior{
    public:
        enum{
            MOVE_UP,
            MOVE_DOWN,
            MOVE_LEFT,
            MOVE_RIGHT,
            SPTR_RIGHT,
            SPTR_LEFT
        };
        GameObject* main_camera;
        float speed = 2.5;
        InputHandler ih = InputHandler(6);
        SpriteRenderer* sprite_rend;
        void Begin() override{
            main_camera = Scene::active_scene->FindGameObject("Main Camera");
            ih.AddCommandBack(GLFW_KEY_W,PressType::KEY_HOLD,MOVE_UP);
            ih.AddCommandBack(GLFW_KEY_S,PressType::KEY_HOLD,MOVE_DOWN);
            ih.AddCommandBack(GLFW_KEY_A,PressType::KEY_HOLD,MOVE_LEFT);
            ih.AddCommandBack(GLFW_KEY_D,PressType::KEY_HOLD,MOVE_RIGHT);
            ih.AddCommandBack(GLFW_KEY_LEFT,PressType::KEY_PRESS,SPTR_LEFT);
            ih.AddCommandBack(GLFW_KEY_RIGHT,PressType::KEY_PRESS,SPTR_RIGHT);
            sprite_rend = game_object->GetComponent<SpriteRenderer>();
        }
        void EarlyUpdate() override{
            Vector3 mov_direction;
            ih.HandleInput();
            if(ih.GetInputInfo(MOVE_UP).was_activated){
                mov_direction += Vector3(0.0,1.0,0.0);
            }
            if(ih.GetInputInfo(MOVE_DOWN).was_activated){
                mov_direction -= Vector3(0.0,1.0,0.0);
            }
            if(ih.GetInputInfo(MOVE_LEFT).was_activated){
                mov_direction -= Vector3(1.0,0.0,0.0);
            }
            if(ih.GetInputInfo(MOVE_RIGHT).was_activated){
                mov_direction += Vector3(1.0,0.0,0.0);
            }
            if(ih.GetInputInfo(SPTR_RIGHT).was_activated){
                sprite_rend->SetAtlasCoordinate(Vector2(sprite_rend->AtlasCoords().x+1,sprite_rend->AtlasCoords().y));
            }
            if(ih.GetInputInfo(SPTR_LEFT).was_activated){
                sprite_rend->SetAtlasCoordinate(Vector2(sprite_rend->AtlasCoords().x-1,sprite_rend->AtlasCoords().y));
            }
            Vector3 mov_final = Vector::Normalize(mov_direction)*speed*Time::deltaTime;
            this->transform->Translate(mov_final);
            //main_camera->transform->Translate(mov_final);
        }
};