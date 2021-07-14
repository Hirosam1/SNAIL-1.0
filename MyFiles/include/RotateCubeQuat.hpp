#pragma once
#include "GameEngine.hpp"

class RotateCubeQuat : public Behavior{
    public:
        enum PosKeys{
            CHANGE_POS_PRESS,
            CHANGE_POS_RELEASE
        };
        float speed = 0.3;

        Vector3 pos_A;
        Vector3 pos_B = Vector3(3.0,-1.5,1.0);
        Vector3 pos_prev;
        Vector3 pos_target;

        Quaternion rot_A = Quaternion();
        Quaternion rot_B;
        Quaternion rot_prev;
        Quaternion rot_target;

        float time_duration = 4.0;
        float time_elapsed = 0.0;

        InputHandler ih = InputHandler(1);
        void Begin() override{
            rot_B = Quaternion(Vector3(0.0,1.0,0.0), Math::ToRadians(90));
            rot_B = rot_B * Quaternion(Vector3(1.0,0.0,0.0), Math::ToRadians(90));
            pos_A = transform->position;

            rot_target = rot_B;
            pos_target = pos_B;
            pos_prev = pos_A;
            rot_prev = rot_A;

            ih.AddCommandBack(GLFW_KEY_Z,PressType::KEY_PRESS,CHANGE_POS_PRESS);
        }

        void Update() override{
            ih.HandleInput();
            float t =time_elapsed/time_duration;
            if(ih.GetInputInfo(CHANGE_POS_PRESS).was_activated){
                if(pos_target == pos_B){
                    pos_target = pos_A;
                    rot_target = rot_A;
                    pos_prev = pos_B;
                    rot_prev = rot_B;
                }else{
                    pos_target = pos_B;
                    rot_target = rot_B;
                    pos_prev = pos_A;
                    rot_prev = rot_A;
                }
                float p_dist = 1.0 - t;
                time_elapsed = p_dist * time_duration;
                t = time_elapsed/time_duration;
            }
           
            if(t < 1.0){
                time_elapsed += Time::deltaTime;
                transform->position = Vector::Lerp(pos_prev,pos_target, t);
                transform->rotation = rot_prev.Slerp(rot_target, t);
            }
        } 
};
