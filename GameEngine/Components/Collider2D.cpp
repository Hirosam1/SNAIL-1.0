#include "Components/Collider2D.hpp"

Intersect2DInfo Circle2D::IntersectCollider2D(const Collider2D& other){
    const Circle2D* other_cirlce;
    if((other_cirlce = dynamic_cast<const Circle2D*>(&other))){
        float radius_distance = this->radius + other_cirlce->radius;
        float center_distance = Vector::Length(Vector3(other_cirlce->center_position.x,other_cirlce->center_position.y,0) - 
                                Vector3(this->center_position.x,this->center_position.y,0)); 
        if(center_distance< radius_distance){
            return Intersect2DInfo{true,center_distance - radius_distance};
        }else{
            return Intersect2DInfo{false, center_distance - radius_distance};
        }
    }
}