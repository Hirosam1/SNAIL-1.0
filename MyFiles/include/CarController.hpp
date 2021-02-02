#pragma once
#include "GameEngine.hpp"
#include "math.h"
//In this case it is not necessary to separate definition from 
//declaration because there is no circular dependecy, but if it had
//It would be necessary


enum Controlls{
    MOVE_FORWARDS,
    MOVE_BACKWARDS,
    TURN_LEFT,
    TURN_RIGHT
};

class CarController : public Behaviour{
    public:
        float top_velocity = 3.0f;
        float accel = 1.0f;
        float deccel = 0.7f;
        Vector3 front_vector = Vector3(0.0f,1.0f,0.0f);
        Vector3 right_vector = Vector3(1.0f,0.0f,0.0f);
        const Vector3 up_vector = Vector3(0.0f,0.0f,1.0f);
        InputHandler ih = InputHandler(4);
        void Begin() override;

        void Update() override;
};