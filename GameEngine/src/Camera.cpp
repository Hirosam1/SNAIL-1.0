#include "Camera.hpp"

Camera::Camera(){
    camera_front = Vector3(0.0f,0.0f,-1.0f);
    camera_up = Vector3(0.0f,1.0f,0.0f);
    view = Transformation::CamLookAt(camera_pos, camera_pos + camera_front, camera_up);
}

const Matrix4& Camera::SetCameraPos(const Vector3& pos){
    camera_pos = pos;
    //view = Transformation::CamLookAt(camera_pos, camera_pos + camera_front, camera_up);
    return view;
}

const Matrix4& Camera::SetCameraDir(const Vector3& dir){
    camera_front = dir;
    //view = Transformation::CamLookAt(camera_pos, camera_pos + camera_front, camera_up);
    return view;
}

const Matrix4& Camera::MoveCameraPos(const Vector3& pos){
    camera_pos = camera_pos + pos;
    //view = Transformation::CamLookAt(camera_pos, camera_pos + camera_front, camera_up);
    return view;
}

void Camera::BuildMat(){
    view = Transformation::CamLookAt(camera_pos, camera_pos + camera_front, camera_up);
}

const Matrix4& Camera::View() const{
    return view;
}

const Vector3& Camera::Pos() const{
    return camera_pos;
}

const Vector3& Camera::Front() const{
    return camera_front;
}

const Vector3& Camera::Up() const{
    return camera_up;
}