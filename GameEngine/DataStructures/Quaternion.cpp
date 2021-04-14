#include "DataStructures/Quaternion.hpp"

Quaternion::Quaternion(int x, int y, int z, int w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

float Quaternion::Length() const{
    return qsqrt(x*x+y*y+z*z+w*w);
}

Quaternion Quaternion::Normalize() const{
    float length = this->Length();

    float _x = x/length;
    float _y = y/length;
    float _z = z/length;
    float _w = w/length;
    return Quaternion(_x,_y,_z,_w);
}

Quaternion Quaternion::Conjugate() const{
    return Quaternion(-x,-y,-z,w);
}

Quaternion Quaternion::Multiply(const Quaternion& quat) const{
    float _x,_y,_z,_w;

    _w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
    _x = x * quat.w + w * quat.x + y * quat.z - z * quat.y;
    _y = y * quat.w + w * quat.y + z * quat.x - x * quat.z;
    _z = z * quat.w + w * quat.z + x * quat.y - y * quat.x;

    return Quaternion(_x,_y,_z,_w);
}

Quaternion Quaternion::Multiply(const Vector3& vec) const{
    float _w = -x * vec.x - y * vec.y - z * vec.z;
    float _x =  w * vec.x + y * vec.z - z * vec.y;
    float _y =  w * vec.y + z * vec.x - x * vec.z;
    float _z =  w * vec.z + x * vec.y - y * vec.x;

    return Quaternion(_x,_y,_z,_w);
}

Matrix4 Quaternion::BuildRotMat() const{
    Quaternion quat = this->Normalize();
    float qx = quat.x;
    float qy = quat.y;
    float qz = quat.z;
    float qw = quat.w;

    Matrix4 mat = Matrix4(1.0);

    mat.mat[0] = 1.0 - 2.0*qy*qy - 2.0*qz*qz;
    mat.mat[1] = 2.0f*qx*qy + 2.0f*qz*qw;
    mat.mat[2] = 2.0f*qx*qz - 2.0f*qy*qw;

    mat.mat[4] = 2.0f*qx*qy - 2.0f*qz*qw;
    mat.mat[5] = 1.0f - 2.0f*qx*qx - 2.0f*qz*qz;
    mat.mat[6] = 2.0f*qy*qz + 2.0f*qx*qw;

    mat.mat[8] = 2.0f*qx*qz - 2.0f*qy*qw;
    mat.mat[9] = 2.0f*qy*qz - 2.0f*qx*qw;
    mat.mat[10]= 1.0f - 2.0f*qx*qx - 2.0f*qy*qy;

    return mat;
}

/*
    <T>
    1.0f - 2.0f*qy*qy - 2.0f*qz*qz,  2.0f*qx*qy - 2.0f*qz*qw,        2.0f*qx*qz + 2.0f*qy*qw,        0.0f,
    2.0f*qx*qy + 2.0f*qz*qw,         1.0f - 2.0f*qx*qx - 2.0f*qz*qz, 2.0f*qy*qz - 2.0f*qx*qw,        0.0f,
    2.0f*qx*qz - 2.0f*qy*qw,         2.0f*qy*qz + 2.0f*qx*qw,        1.0f - 2.0f*qx*qx - 2.0f*qy*qy, 0.0f,
    0.0f,                            0.0f,                           0.0f,                           1.0f);
*/