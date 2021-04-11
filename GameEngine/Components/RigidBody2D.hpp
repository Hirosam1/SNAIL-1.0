#pragma once
#include "Components/Component.hpp"
#include "Vector.hpp"
#include "Transform.hpp"

class Collider2D;

class RigidBody2D : public Component{
    public:
        Collider2D* collider;
};