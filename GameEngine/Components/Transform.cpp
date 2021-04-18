#include "Components/Transform.hpp"

Transform::Transform(){
    position = Vector3();
    rotation = Quaternion();
    scale = Vector3(1.0f,1.0f,1.0f);
    model_mat = Matrix4(1.0);
    BuildMat();
}

Transform::Transform(const Vector3& pos, const Vector3& rot, const Vector3& scale): position(pos), 
                                                                                    rotation(Transformation::EulerToQuaternion(rot)), 
                                                                                    scale(scale){
    BuildMat();
}

Transform::Transform(const Vector3& pos, const Quaternion& rot, const Vector3& scale) : position(pos), rotation(rot), scale(scale){BuildMat();}

void Transform::BuildMat(){
    model_mat = Transformation::Translate( Matrix4(1.0f),position);
    model_mat = model_mat * rotation.BuildRotMat();
    model_mat = Transformation::Scale(model_mat,scale);
}

Vector3 Transform::Front() const{
    Vector4 front_4 = model_mat.Row(2);
    return Vector3(front_4.x,front_4.y,front_4.z);
}

void Transform::Update(GameObject* game_object){
    BuildMat();
}

void Transform::SetPos(const Vector3& pos){
    position = pos;
}

Vector3 Transform::Translate(const Vector3& move_pos){
    position += move_pos;
    return position;
}

void Transform::SetScale(const Vector3& scale){
    this->scale = scale;
}

void Transform::SetRot(const Vector3& rot){
    rotation = Transformation::EulerToQuaternion(rot);
}

void Transform::SetRot(const Quaternion& quat){
    rotation = quat;
}

void Transform::Rotate(const Vector3& rot){
    rotation = Transformation::EulerToQuaternion(rot) * rotation;
}

void Transform::Rotate(const Quaternion& quad){
    rotation = quad * rotation;
}


void Transform::LookAt(const Vector3& target){
    rotation = Transformation::Matrix4ToQuaternion(Transformation::LookAt(position,target,Vector3(0.0,1.0,0.0f)));
}

const Matrix4& Transform::ModelMat() const{
    return model_mat;
}

const Vector3& Transform::Scale() const{
    return scale;
}

const Vector3& Transform::Pos() const{
    return position;
}

const Quaternion& Transform::Rot() const{
    return rotation;
}