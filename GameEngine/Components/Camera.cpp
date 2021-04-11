#include "Components/Camera.hpp"

Camera::Camera(Camera_Projection camera_projection){
    Window* a_window = Window::main_window;
    camera_front = Vector3(0.0f,0.0f,-1.0f);
    camera_up = Vector3(0.0f,1.0f,0.0f);
    //view = Transformation::CamLookAt(Vector3(0.0,0.0,1.0), Vector3(0.0,0.0,1.0) + camera_front, camera_up);
    //Perspective Configuration---------------------------------------------
    near_plane = .15f;
    far_plane = 100.0f;
    proj_info.projection_function = camera_projection == Camera_Projection::PERSPECTIVE_PROJECTION ? Projection::Perspective : 
                                                camera_projection == Camera_Projection::ORTHOGRAPHIC_PROJECTION? Projection::Orthographic : Projection::Orthographic;
    BuildProj();
    BuildMat();
    BuildFrustum();
   
}

void Camera::BuildProj(){
    proj_info.projection = proj_info.projection_function(proj_info.FOV, Window::main_window->width/(float)Window::main_window->height,near_plane,far_plane,proj_info.ortho_size);

}

void Camera::BuildFrustum(){
    const float* projection = view_projection.mat;
    float n;
    frustum.left = Plane3{ Vector3(projection[3] + projection[0], projection[7] + projection[4], projection[11] + projection[8]), projection[15] + projection[12] };
    frustum.right = Plane3{Vector3(projection[3] - projection[0], projection[7] - projection[4], projection[11] - projection[8]), projection[15] - projection[12]};

    frustum.bottom = Plane3{Vector3(projection[3] + projection[1], projection[7] + projection[5], projection[11] + projection[9]), projection[15] + projection[13]};
    frustum.top =    Plane3{Vector3(projection[3] - projection[1], projection[7] - projection[5], projection[11] - projection[9]), projection[15] - projection[13]};

    frustum.near = Plane3{Vector3(projection[3] + projection[2], projection[7] + projection[6], projection[11] + projection[10]), projection[15] + projection[14]};
    frustum.far =  Plane3{Vector3(projection[3] - projection[2], projection[7] - projection[6], projection[11] - projection[10]), projection[15] - projection[14]};


}

void Camera::NormalizeFrustum(){
    float n;
    frustum.left = NormalizePlane(frustum.left,&n);
    frustum.right = NormalizePlaneWithLength(frustum.right,n);

    frustum.top = NormalizePlane(frustum.top,&n);
    frustum.bottom = NormalizePlaneWithLength(frustum.bottom,n);

    frustum.near = NormalizePlane(frustum.near,&n);
    frustum.far = NormalizePlaneWithLength(frustum.far,n);
}



void Camera::SetCameraDir(const Vector3& dir){
    camera_front = dir;
    //view = Transformation::CamLookAt(camera_pos, camera_pos + camera_front, camera_up);
}
void Camera::LookAt(const Vector3& target, const Vector3& up){
    if(game_object){
        Transform* tranform = game_object->transform;
        tranform->SetRot(Transformation::ExtractEulerFromMat(Transformation::CamLookAt(tranform->Pos(),tranform->Pos() + target,up)));
    }
}

void Camera::BuildMat(){
    if(game_object){
        Transform* tranform = game_object->transform;
        view = Matrix4(1.0f);
        view = Transformation::RotateX(view,tranform->Rot().x);
        view = Transformation::RotateY(view,tranform->Rot().y);
        view = Transformation::RotateZ(view,tranform->Rot().z);
        view = Transformation::Translate(view, -tranform->Pos());
        Vector4 column = tranform->ModelMat().Column(2);
        camera_front = -Vector3(column.x,column.y,column.z);
    }
    view_projection = proj_info.projection * view;
}

void Camera::Update(GameObject* game_object){
    BuildProj();
    BuildMat();
    BuildFrustum();
    NormalizeFrustum();
}

const Matrix4& Camera::View() const{
    return view;
}

const Matrix4& Camera::Projection() const{
    return proj_info.projection;
}

const Matrix4& Camera::ViewProjection() const{
    return view_projection;
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

const ViewFrustum& Camera::Frustum() const{
    return frustum;
}