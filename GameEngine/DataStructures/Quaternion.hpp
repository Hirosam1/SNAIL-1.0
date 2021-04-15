#pragma once
#include "GMpch.hpp"

#include "DataStructures/Vector.hpp"
#include "DataStructures/Matrix.hpp"

#include "Math/Math.hpp"


struct AxisAngle
{
        Vector3 axis = Vector3();
        float angle = 0;
};

class Quaternion {
    public:
        Quaternion();
        Quaternion(float x, float y, float z, float w);
        Quaternion(const Vector3& axis, float rad_angle);
        Quaternion Conjugate() const;
        //Multiply by "adding" two quaternions together
        Quaternion Multiply(const Quaternion& quat) const;
        //Returns the inverse of a quaternion, usefull for "undoing" quaternions
        Quaternion Inverse() const;
        //Power of the quaternion, meaning a percentage of a rotation
        Quaternion Pow(float t);
        // Quaternion Multiply(const Vector3& vec3) const;
        float Length() const;
        Quaternion Normalize() const;
        //Convert quaternions to Rodriguez axis angle rotation
        AxisAngle QuaternionToAxisAngle();
        //Convert Rodriguez angle axis rotation back to quaternions
        Quaternion AxisAngleToQuaternion(const AxisAngle& axis_angle) const;
        //Spherical interpolation
        Quaternion Slerp(const Quaternion& end, float t);


        // Matrix4 BuildRotMat() const;
        float x,y,z,w;
};

std::ostream& operator<<(std::ostream& stream, const Quaternion& other);