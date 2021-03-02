#include "GameEngine.hpp"

class MovingObject : public Behaviour{
    public:
        float range_multiplier;
        float x_init;

        void Begin() override{
            x_init = transform->Pos().x;
        }
        void Update() override{
            transform->SetPos(Vector3(sin(Time::GetTime()) + x_init,transform->Pos().y,transform->Pos().z));
        }
};