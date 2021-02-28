#pragma once
#include "Vector.hpp"
#include "Math.hpp"

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
    float d; 
};


Plane3 NormalizePlane(Plane3 plane, float* n = nullptr);
Plane3 NormalizePlaneWithLength(Plane3 plane, float length);

Vector3 IntersectionPoint(Line3 a, Line3 b);
Vector3 IntersectionPoint(Line3 a, Plane3 b);
Vector3 VectorProjection(Vector3 surface, Vector3 original);
float DistancePlanePoint(Plane3 plane, Vector3 point);