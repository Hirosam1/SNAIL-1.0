#pragma once
#include "DataStructures/Vector.hpp"
#include "DataStructures/Quaternion.hpp"

namespace Transformation{    
    inline Vector3 QuaternionToEuler(const Quaternion& quat){
        return Transformation::ExtractEulerFromMat(quat.BuildRotMat());     
    }

    inline Quaternion EulerToQuaternion(const Vector3& vec){
        float sin_x = sin(vec.x/2.0f);
        float cos_x = cos(vec.x/2.0f);

        float sin_y = sin(vec.y/2.0f);
        float cos_y = cos(vec.y/2.0f);

        float sin_z = sin(vec.z/2.0f);
        float cos_z = cos(vec.z/2.0f);
        //convert this rotation to quaternion
        float _x = sin_x * cos_y * cos_z - cos_x * sin_y * sin_z;
        float _y = cos_x * sin_y * cos_z + sin_x * cos_y * sin_z;
        float _z = cos_x * cos_y * sin_z - sin_x * sin_y * cos_z;
        float _w = cos_x * cos_y * cos_z + sin_x * sin_y * sin_z;

        return Quaternion(_x,_y,_z,_w);
    }
}
/*
    
    this->x = s.x * c.y * c.z - c.x * s.y * s.z;
    this->y = c.x * s.y * c.z + s.x * c.y * s.z;
    this->z = c.x * c.y * s.z - s.x * s.y * c.z; 
    this->w = c.x * c.y * c.z + s.x * s.y * s.z;
*/

//
//x = z
//y = x
//z = y