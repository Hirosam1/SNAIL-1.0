#pragma once
#include "Components/Component.hpp"

#include "DataStructures/Vector.hpp"

#include "Transform.hpp"

#include "Math/Math.hpp"

struct Intersect2DInfo{
        Intersect2DInfo(bool _intersect, float distance): did_intersect(_intersect), distance(distance){};
        const bool did_intersect;
        const float distance;
};

class Collider2D : public Component{
    public:
        void Begin(GameObject* game_object){this->game_object = game_object;}
        void Update(GameObject* game_object){};
        virtual Intersect2DInfo IntersectCollider2D(const Collider2D& other_col) = 0;
        GameObject* game_object;
    
};

class Circle2D : public Collider2D{
    public:
        Intersect2DInfo IntersectCollider2D(const Collider2D& other_col) override;
        Vector3 center_position;
        float radius;
};