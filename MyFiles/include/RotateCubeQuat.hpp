#pragma once
#include "GameEngine.hpp"

class RotateCubeQuat : public Behaviour{
    public:
        float rot_speed = 1.0;
        void Update() override{
            transform->Rotate(Quaternion(Vector3(0.0,1.0,0.0),rot_speed* Time::deltaTime));
        }
};
