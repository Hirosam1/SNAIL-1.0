#pragma once
#include "DataStructures/Vector.hpp"
#include "DataStructures/Quaternion.hpp"

namespace Quat{
    inline Vector3 QuaternionToEuler(const Quaternion& quat){
        return quat.QuaternionToEuler();
    }

    inline Quaternion EulerToQuaternion(const Vector3& vec){
        float sin_x = sin(vec.x/2.0f);
        float cos_x = cos(vec.x/2.0f);

        float sin_y = sin(vec.y/2.0f);
        float cos_y = cos(vec.y/2.0f); 

        float sin_z = sin(vec.z/2.0f);
        float cos_z = cos(vec.z/2.0f);
        //This looks like XYZ application order? Why does it works with camera->LookAt??
        return Quaternion(
            sin_x*cos_y*cos_z + cos_x*sin_y*sin_z,
            cos_x*sin_y*cos_z - sin_x*cos_y*sin_z,
            cos_x*cos_y*sin_z + sin_x*sin_y*cos_z,
            cos_x*cos_y*cos_z - sin_x*sin_y*sin_z);
    }

    inline Quaternion Matrix4ToQuaternion(const Matrix4& rot_mat){
        float fourXSquaredMinus1 = rot_mat[0][0] - rot_mat[1][1] - rot_mat[2][2];
        float fourYSquaredMinus1 = rot_mat[1][1] - rot_mat[0][0] - rot_mat[2][2];
        float fourZSquaredMinus1 = rot_mat[2][2] - rot_mat[0][0] - rot_mat[1][1];
        float fourWSquaredMinus1 = rot_mat[0][0] + rot_mat[1][1] + rot_mat[2][2];

        int biggestIndex = 0;
        float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
        if(fourXSquaredMinus1 > fourBiggestSquaredMinus1){
            fourBiggestSquaredMinus1 = fourXSquaredMinus1;
            biggestIndex = 1;
        }
        if(fourYSquaredMinus1 > fourBiggestSquaredMinus1){
            fourBiggestSquaredMinus1 = fourYSquaredMinus1;
            biggestIndex = 2;
        }
        if(fourZSquaredMinus1 > fourBiggestSquaredMinus1){
            fourBiggestSquaredMinus1 = fourZSquaredMinus1;
            biggestIndex = 3;
        }

        float biggestVal = Math::qsqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
        float mult = 0.25f/ biggestVal;

        switch (biggestIndex)
        {
            case 0:
                return Quaternion((rot_mat[1][2] - rot_mat[2][1]) * mult,
                                (rot_mat[2][0] - rot_mat[0][2]) * mult,
                                (rot_mat[0][1] - rot_mat[1][0]) *  mult,
                                biggestVal);
            case 1:
                return Quaternion(biggestVal, 
                                (rot_mat[0][1] + rot_mat[1][0]) * mult, 
                                (rot_mat[2][0] + rot_mat[0][2]) * mult, 
                                (rot_mat[1][2] - rot_mat[2][1]) * mult);
            case 2:
                return Quaternion((rot_mat[0][1] + rot_mat[1][0]) * mult,
                                biggestVal,
                                (rot_mat[1][2] + rot_mat[2][1]) * mult,
                                (rot_mat[2][0] - rot_mat[0][2]) * mult);
            case 3:
                return Quaternion((rot_mat[2][0] + rot_mat[0][2]) * mult,
                                (rot_mat[1][2] + rot_mat[2][1]) * mult,
                                biggestVal,
                                (rot_mat[0][1] - rot_mat[1][0]) * mult);
            default:
                return Quaternion(0.0f,0.0f,0.0f,1.0f);
        }
    }

}