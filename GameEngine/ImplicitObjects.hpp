#pragma once
#include "Vector.hpp"

namespace ImplicitVolumes{
    struct AABB{
        Vector3 min;
        Vector3 max;
    };
    struct Sphere{
        float radius;
        Vector3 position;
    };
};

struct Line3{
    Vector3 direction;
    Vector3 point;
};

struct Plane3{
    Vector3 normal; 
    Vector3 d; 
};



Vector3 IntersectionPoint(Line3 a, Line3 b);
Vector3 IntersectionPoint(Line3 a, Plane3 b);
Vector3 VectorProjection(Vector3 surface, Vector3 original);