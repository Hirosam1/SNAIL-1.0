#pragma once
#include "GMpch.hpp"

#include "DataStructures/Vector.hpp"
#include "DataStructures/Matrix.hpp"

#include "Math/Math.hpp"

class Quaternion {
    public:
        Quaternion(int x, int y, int z, int w);
        Quaternion Conjugate() const;
        Quaternion Multiply(const Quaternion& quat) const;
        Quaternion Multiply(const Vector3& vec3) const;
        float Length() const;
        Quaternion Normalize() const;
        Matrix4 BuildRotMat() const;
        float x,y,z,w;
};