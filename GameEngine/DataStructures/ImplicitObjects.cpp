#include "DataStructures/ImplicitObjects.hpp"

Vector3 IntersectionPoint(Line3 a, Line3 b){
    //get the parametric form of te line
    Vector3 a_p1 = a.point;
    Vector3 b_p1 = b.point;
    
    Vector3 cross = a.direction.Cross(b.direction);
    float denominator = cross.Dot(cross);
    if(denominator == 0){
        return Vector3(NAN,NAN,NAN);
    }
    float t = ((b_p1 - a_p1).Cross(b.direction).Dot(cross))/denominator;
    return a_p1 + t * a.direction;
}

Vector3 VectorProjection(Vector3 surface, Vector3 original){
    float denominator = surface.Dot(surface);
    if(denominator == 0){
        return Vector3(NAN,NAN,NAN);
    }
    return original.Dot(surface)/denominator * surface;
}

Plane3 NormalizePlane(Plane3 plane, float* n){
    float _n;
    _n = qsqrt(plane.normal.x*plane.normal.x + plane.normal.y*plane.normal.y + plane.normal.z*plane.normal.z);
    plane.normal = plane.normal/_n;
    plane.d = plane.d/_n;
    if(n != nullptr){
        *n = _n;
    }
    return plane;
}

Plane3 NormalizePlaneWithLength(Plane3 plane, float length){
    plane.normal = plane.normal/length;
    plane.d = plane.d/length;
    return plane;
}

float DistancePlanePoint(Plane3 plane, Vector3 point){
    return plane.normal.x*point.x + plane.normal.y*point.y + plane.normal.z*point.z + plane.d;
}