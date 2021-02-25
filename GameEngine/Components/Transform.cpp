#include "Components/Transform.hpp"

Transform::Transform(){
    position = Vector3();
    rotation = Vector3();
    scale = Vector3(1.0f,1.0f,1.0f);
    model_mat = Matrix4(1.0);
    BuildMat();
}

Transform::Transform(const Vector3& pos, const Vector3& rot, const Vector3& scale): position(pos), rotation(rot), scale(scale){
    BuildMat();
}

void Transform::BuildMat(){
    model_mat = Transformation::Translate( Matrix4(1.0f),position);
    model_mat = Transformation::RotateZ(model_mat,rotation.z);
    model_mat = Transformation::RotateY(model_mat,rotation.y);
    model_mat = Transformation::RotateX(model_mat,rotation.x);
    model_mat = Transformation::Scale(model_mat,scale);
}

void Transform::Update(GameObject* game_object){
    BuildMat();
}

void Transform::SetPos(const Vector3& pos){
    position = pos;
    //BuildMat();
}

Vector3 Transform::MovePos(const Vector3& move_pos){
    position += move_pos;
    //BuildMat();
    return position;
}

void Transform::SetScale(const Vector3& scale){
    this->scale = scale;
    //BuildMat();
}

void Transform::SetRot(const Vector3& rot){
    rotation = rot;
    //BuildMat();
}

void Transform::AddRot(const Vector3& rot){
    rotation = rotation + rot;
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

const Vector3& Transform::Rot() const{
    return rotation;
}