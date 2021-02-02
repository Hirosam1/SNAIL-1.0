#pragma once
#include "GameEngine.hpp"
#include "CarController.hpp"

class CarFollower : public  Behaviour{
    public:
        float velocity = 1.0;
        GameObject* car = nullptr;
        void Begin() override;

        void Update() override;

};