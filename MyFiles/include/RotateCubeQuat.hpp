#pragma once
#include "GameEngine.hpp"

class RotateCubeQuat : public Behaviour{
    public:
        float rot_speed = 5.0;
        //This should be quat identity
        Quaternion quat = Quaternion(0.0,0.0,0.0,1.0);
        void Begin() override{

        }

        void Update() override{
            transform->Rotate(Quaternion(Vector3(0.0,0.0,1.0),rot_speed* Time::deltaTime));
        }
};
