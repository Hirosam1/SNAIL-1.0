#pragma once
#include "GMpch.hpp"
#include "Components/Component.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"
#include "Math.hpp"
#include "Matrix_Transform.hpp"
#include "Window.hpp"
#include "ImplicitObjects.hpp"
#include "GameObject.hpp"

enum Camera_Projection{
    PERSPECTIVE_PROJECTION,
    ORTHOGRAPHIC_PROJECTION
};

struct ProjectionInfo{
    Matrix4 projection;
    float FOV = ToRadians(50.0f);
    float ortho_size = 3.0;
    Matrix4(*projection_function)(float,float ,float ,float, float);
};

struct ViewFrustum{
    Plane3 near;
    Plane3 left;
    Plane3 right;
    Plane3 far;
    Plane3 top;
    Plane3 bottom;
};

class Camera : public Component{
    public:
        Camera(Camera_Projection camera_projection = Camera_Projection::ORTHOGRAPHIC_PROJECTION);
        //Sets the camera to desired position
        void SetCameraPos(const Vector3& pos);
        //Sets the camera direction (looking at) direction
        void SetCameraDir(const Vector3& dir);
        //Looks at target with up vector
        void LookAt(const Vector3& target, const Vector3& up);
        //Build the projection matrix
        void BuildProj();
        //The update method for updating the matrix information
        void Update(GameObject* game_object) override;
        //Returns the view matrix
        const Matrix4& View() const;
        //Returns the projection matrix of the camera
        const Matrix4& Projection() const;
        //Returns the VP (View Projection) matrix already multiplied, to be used with a model matrix
        const Matrix4& ViewProjection() const;
        //Returns the up vector of the camera
        const Vector3& Up() const;
        //Returns the front vector of the camera
        const Vector3& Front() const;
        //Returns the projection info of the camera
        const ProjectionInfo& ProjInfo() const;
        //Returns the view frustum of the camera
        const ViewFrustum& Frustum() const;

        float near_plane;
        float far_plane;
        
    private:
        //Build the camera matrix given the position and front vectors
        void BuildMat();
        void NormalizeFrustum();
        //Build view frustum info
        void BuildFrustum();
        //Frustum planes 
        ViewFrustum frustum;
        //View matrix
        Matrix4 view;
        // View * projection matrix
        Matrix4 view_projection;
        //Projection propierties
        ProjectionInfo proj_info;
        Vector3 camera_front;
        Vector3 camera_up;
};