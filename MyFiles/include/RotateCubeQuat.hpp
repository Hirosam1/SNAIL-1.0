#pragma once
#include "GameEngine.hpp"

class RotateCubeQuat : public Behaviour{
    public:
        float rot_speed = 0.3;
        Quaternion rot_target = Quaternion(Vector3(0.0,1.0,0.0),Math::ToRadians(90));
        Quaternion current = Quaternion();

        void Begin() override{
            
           
        }

        void Update() override{
            // transform->Rotate(Quaternion(Vector3(0.0,1.0,0.0),rot_speed* Time::deltaTime));
            current = current.Slerp(rot_target, rot_speed * Time::deltaTime);
            transform->SetRot(current);

        }
};
