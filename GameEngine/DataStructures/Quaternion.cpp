#include "DataStructures/Quaternion.hpp"


Quaternion::Quaternion(): x(0.0f), y(0.0f), z(0.0f), w(1.0f){
}

Quaternion::Quaternion(float x, float y, float z, float w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::Quaternion(const Vector3& axis, float rad_angle){
    w = cos(rad_angle/2.0f);
    float sin_a = sin(rad_angle/2.0f);
    axis = Math::Normalize(axis);
    x = sin_a * axis.x;
    y = sin_a * axis.y;
    z = sin_a * axis.z;

}

float Quaternion::Length() const{
    return Math::qsqrt(x*x+y*y+z*z+w*w);
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
    Vector3 v_r = Vector3(x,y,z);
    Vector3 v_s = Vector3(quat.x,quat.y,quat.z);
    float v_w = quat.w*w - v_s.Dot(v_r);
    Vector3 v = quat.w * v_r + w * v_s + v_r.Cross(v_s);
    return Quaternion(v.x,v.y,v.z,v_w);
}

Quaternion Quaternion::Pow(float p) const{
    AxisAngle a_a = this->QuaternionToAxisAngle();
    a_a.angle *= abs(p);
    return Quaternion(a_a.axis,a_a.angle); 
}

Quaternion Quaternion::Inverse() const{
    float length =  Math::Length(Vector3(x,y,z));
    float q_sqr = w*w + length*length;
    float _w = w/q_sqr;
    Vector3 v = -Vector3(x,y,z)/q_sqr;
    return Quaternion(v.x,v.y,v.z,_w);
}


AxisAngle Quaternion::QuaternionToAxisAngle() const{
    Vector3 axis = Math::Normalize(Vector3(x,y,z));
    float angle = acos(w) * 2.0f;
    return AxisAngle{axis,angle};
    
}

Quaternion Quaternion::AxisAngleToQuaternion(const AxisAngle& a_a) const{
    return Quaternion(a_a.axis,a_a.angle);
}

Quaternion Quaternion::Slerp(const Quaternion& end, float t) const{
    //a -> start
    //b -> end
    //t -> percentage 
    //reads from right to left
    //(b - a)*t + a

    return (end * this->Inverse()).Pow(t) * *this;
}

Vector3 Quaternion::Vec() const{
    return Vector3(x,y,z);
}

Quaternion Quaternion::operator*(const Quaternion& quad) const{
    return this->Multiply(quad);
}


Matrix4 Quaternion::BuildRotMat() const{
    Quaternion quat = this->Normalize();
    float qx = quat.x;
    float qy = quat.y;
    float qz = quat.z;
    float qw = quat.w;

    Matrix4 mat = Matrix4(1.0);
    //When converting needs to negate some of the values to the system be right handed
    mat.mat[0] = 1.0 - 2.0 * (qy*qy + qz*qz);
    mat.mat[1] = 2.0 * -(qx*qy - qw*qz);
    mat.mat[2] = 2.0 * -(qx*qz + qw*qy);

    mat.mat[4] = 2.0 * -(qx*qy + qw*qz);
    mat.mat[5] = 1.0 - 2.0 * (qx*qx + qz*qz);
    mat.mat[6] = 2.0 * -(qy*qz - qw*qx);

    mat.mat[8] = 2.0 * -(qx*qz - qw*qy);
    mat.mat[9] = 2.0 * -(qy*qz + qw*qx);
    mat.mat[10]= 1.0 - 2.0 * (qx*qx + qy*qy);

    return mat;
}

/* GLM
		Result[0][0] = T(1) - T(2) * (qyy +  qzz);
		Result[0][1] = T(2) * (qxy + qwz);
		Result[0][2] = T(2) * (qxz - qwy);

		Result[1][0] = T(2) * (qxy - qwz);
		Result[1][1] = T(1) - T(2) * (qxx +  qzz);
		Result[1][2] = T(2) * (qyz + qwx);

		Result[2][0] = T(2) * (qxz + qwy);
		Result[2][1] = T(2) * (qyz - qwx);
		Result[2][2] = T(1) - T(2) * (qxx +  qyy);
*/

std::ostream& operator<<(std::ostream& stream, const Quaternion& other){
    stream <<"(" <<other.x <<", " << other.y <<", " <<other.z<<", " << other.w <<")";
    return stream;
}