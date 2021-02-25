#include "ImplicitObjects.hpp"

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
