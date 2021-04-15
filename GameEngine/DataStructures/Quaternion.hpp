#pragma once
#include "GMpch.hpp"

#include "DataStructures/Vector.hpp"
#include "DataStructures/Matrix.hpp"

#include "Math/Math.hpp"

class Quaternion {
    public:
        Quaternion(float x, float y, float z, float w);
        Quaternion(const Vector3& axis, float rad_angle);
        Quaternion Conjugate() const;
        Quaternion Multiply(const Quaternion& quat) const;
        // Quaternion Multiply(const Vector3& vec3) const;
        float Length() const;
        Quaternion Normalize() const;
        // Matrix4 BuildRotMat() const;
        float x,y,z,w;
};

std::ostream& operator<<(std::ostream& stream, const Quaternion& other);