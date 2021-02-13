#include "Camera.hpp"



Camera::Camera(Camera_Projection camera_projection){
    Window* a_window = Window::main_window;
    camera_front = Vector3(0.0f,0.0f,-1.0f);
    camera_up = Vector3(0.0f,1.0f,0.0f);
    view = Transformation::CamLookAt(camera_pos, camera_pos + camera_front, camera_up);
    //Perspective Configuration---------------------------------------------
    near_plane = .15f;
    far_plane = 100.0f;
    proj_info.projection_function = camera_projection == Camera_Projection::PERSPECTIVE_PROJECTION ? Projection::Perspective : 
                                                camera_projection == Camera_Projection::ORTHOGRAPHIC_PROJECTION? Projection::Orthographic : Projection::Orthographic;
    proj_info.projection = proj_info.projection_function(proj_info.FOV, Window::main_window->width/(float)Window::main_window->height,near_plane,far_plane,proj_info.ortho_size);
   
}

void Camera::BuildProj(){
    proj_info.projection = proj_info.projection_function(proj_info.FOV, Window::main_window->width/(float)Window::main_window->height,near_plane,far_plane,proj_info.ortho_size);

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

void Camera::Update(){
    BuildMat();
}

const Matrix4& Camera::View() const{
    return view;
}

const Matrix4& Camera::Projection() const{
    return proj_info.projection;
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

const ProjectionInfo& Camera::ProjInfo() const{
    return proj_info;
}