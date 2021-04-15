#pragma once
#include "GameEngine.hpp"

class RotateCubeQuat : public Behaviour{
    public:
        float speed = 0.3;
        Quaternion rot_target;
        Quaternion current_quat;
        Vector3 current_pos;
        Vector3 pos_target = Vector3(3.0,-1.5,1.0);
        void Begin() override{
            rot_target = Quaternion(Vector3(0.0,1.0,0.0),Math::ToRadians(20));
            //rot_target = rot_target * Quaternion(Vector3(1.0,0.0,0.0),Math::ToRadians(20));
            std::cout<<"Quaternion-> "<<rot_target<<"\n";
            std::cout<<"Euler     -> "<<Transformation::QuaternionToEuler(rot_target)<<"\n";
            current_pos = transform->position;
            transform->SetRot(rot_target);
           
        }

        void Update() override{
            if(Math::Length((rot_target * current_quat.Inverse()).Vec()) > 0.05f){
                // current_pos = Math::Lerp(current_pos,pos_target, speed * Time::deltaTime);
                // current_quat = current_quat.Slerp(rot_target, speed * Time::deltaTime);
                // transform->SetRot(current_quat);
                // transform->SetPos(current_pos);
            }

        } 
};
