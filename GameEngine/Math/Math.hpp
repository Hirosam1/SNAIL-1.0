#pragma once
#include "GMpch.hpp"

#include "DataStructures/Matrix.hpp"
#include "DataStructures/Vector.hpp"

#include "DataStructures/Quaternion.hpp"

#include <algorithm>


namespace Math {
    const float RADIANS = 0.017453292f;

    inline float ToRadians(const float a){
        return a * RADIANS;
    }

    inline float qsqrt(const float &n) 
    {
    static union{int i; float f;} u;
    u.i = 0x5F375A86 - (*(int*)&n >> 1);
    return (int(3) - n * u.f * u.f) * n * u.f * 0.5f;
    }

    inline float Length(const Vector3& vec){
        return qsqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
    }

    inline Vector3 Normalize(const Vector3& vec){
        float l = Math::Length(vec);
        return l > 0? Vector3(vec)/l : Vector3();
    }

    inline float Clamp(float val, float low, float high){
        return val > high ? high : val < low ? low : val;
    }

    inline Vector3 Clamp(const Vector3& val, float low, float high){
        return Vector3(val.x > high ? high : val.x < low ? low : val.x,
                    val.y > high ? high : val.y < low ? low : val.y,
                    val.z > high ? high : val.z < low ? low : val.z);
    }

    inline float Lerp(float start, float end, float t){
        return start + t*(end-start);
    }

    inline Vector3 Lerp(const Vector3& start, const Vector3& end, float t){
        return start + t*(end - start);
    }

    inline Vector4 Lerp(const Vector4& start,const Vector4& end, float t){
        return start + t*(end - start);
    }
    
    // inline Quaternion Lerp(const Quaternion& start, const Quaternion& end,float t){
        
    // }

}