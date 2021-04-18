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

            current_pos = transform->position;
            // transform->Rotate(Quaternion(Vector3(0.0,1.0,0.0),Math::ToRadians(181)));
            // std::cout<<"Quaternion => " << Transformation::EulerToQuaternion(transform->rotation) <<"\n";
            // std::cout<<"Euler      => " << transform->rotation <<"\n";
            
        }

        void Update() override{
            rot_target = Quaternion(Vector3(0.0,1.0,0.0),Math::ToRadians(10 * Time::deltaTime));
            //On rotate it has difficulty rotating past 260(??) degree angle, problem might be in euler-to-quaternion (in rotate)
            // current_quat = rot_target * current_quat;
            // transform->SetRot(current_quat);
            transform->Rotate(rot_target);

        } 
};
