#pragma once
#include "GMpch.hpp"
#include "Components/Component.hpp"
#include "Vector.hpp"
#include "Objects/GameObject.hpp"
#include "Time.hpp"

class Physics : public Component{
    public:
        Vector3 velocity;
        Vector3 acceleration;
        void Update(GameObject* game_object)override;
};