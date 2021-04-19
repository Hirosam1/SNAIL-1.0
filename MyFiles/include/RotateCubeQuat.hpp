#pragma once
#include "GameEngine.hpp"

class RotateCubeQuat : public Behaviour{
    public:
        enum PosKeys{
            CHANGE_POS_PRESS,
            CHANGE_POS_RELEASE
        };
        float speed = 0.3;

        Vector3 pos_A;
        Vector3 pos_B = Vector3(3.0,-1.5,1.0);
        Vector3 pos_target;

        Quaternion rot_A = Quaternion();
        Quaternion rot_B;
        Quaternion rot_target;

        bool released = true;

        InputHandler ih = InputHandler(2);
        void Begin() override{
            rot_B = Quaternion(Vector3(0.0,1.0,0.0), Math::ToRadians(90));
            rot_B = rot_B * Quaternion(Vector3(1.0,0.0,0.0), Math::ToRadians(90));
            pos_A = transform->position;
            rot_target = rot_B;
            pos_target = pos_B;
            ih.AddCommandBack(GLFW_KEY_Z,GLFW_PRESS,CHANGE_POS_PRESS);
            ih.AddCommandBack(GLFW_KEY_Z,GLFW_RELEASE,CHANGE_POS_RELEASE);
        }

        void Update() override{
            ih.HandleInput();

            if(ih.GetInputInfo(CHANGE_POS_PRESS).was_activated && released){
                released= false;
                if(pos_target == pos_B){
                    pos_target = pos_A;
                    rot_target = rot_A;
                }else{
                    pos_target = pos_B;
                    rot_target = rot_B;
                }
            }
            if(ih.GetInputInfo(CHANGE_POS_RELEASE).was_activated){
                released = true;
            }

            if(Math::Length((rot_target * transform->rotation.Inverse()).Vec()) > 0.005f ){
                transform->position = Math::Lerp(transform->position,pos_target,speed * Time::deltaTime);
                transform->rotation = transform->rotation.Slerp(rot_target, speed * Time::deltaTime);
            }else{
                transform->rotation = rot_target;
                transform->position = pos_target;
            }

        } 
};
