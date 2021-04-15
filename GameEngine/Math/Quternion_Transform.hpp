#pragma once
#include "DataStructures/Vector.hpp"
#include "DataStructures/Quaternion.hpp"

namespace Transformation{    
    inline Vector3 QuaternionToEuler(const Quaternion& quat){
        //Convert back to euler
        float x = quat.x;
        float y = quat.y;
        float z = quat.z;
        float w = quat.w;

        float t0 = 2.0 * (w * z + x * y);
        float t1 = 1.0 - 2.0 * (z * z + x * x);
        float t2 = 2.0 * (w * x - y * z);
        t2 =  t2 > 1.0 ? 1.0 :  t2 < -1.0 ? -1.0 : t2;
        float t3 = 2.0 * (w * y + z * x);
        float t4 = 1.0 - 2.0 * (x * x + y * y);

        return Vector3(asin(t2),atan2(t3, t4),atan2(t0, t1));
    }

    inline Quaternion EulerToQuaternion(const Vector3& vec){
        float sin_x = sin(vec.x/2.0f);
        float cos_x = cos(vec.x/2.0f);

        float sin_y = sin(vec.y/2.0f);
        float cos_y = cos(vec.y/2.0f);

        float sin_z = sin(vec.z/2.0f);
        float cos_z = cos(vec.z/2.0f);
        //convert this rotation to quaternion
        float _x = cos_z * sin_x * cos_y + sin_z * cos_x * sin_y; 
        float _y = cos_z * cos_x * sin_y - sin_z * sin_x * cos_y;
        float _z = sin_z * cos_x * cos_y - cos_z * sin_x * sin_y;
        float _w = cos_z * cos_x * cos_y + sin_z * sin_x * sin_y;

        return Quaternion(_x,_y,_z,_w);
    }
}

//
//x = z
//y = x
//z = y