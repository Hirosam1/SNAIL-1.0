#pragma once
#include "GMpch.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Math.hpp"
#include "Matrix_Transform.hpp"
#include "Window.hpp"
#include "Object.hpp"
#include "ImplicitObjects.hpp"

enum Camera_Projection{
    PERSPECTIVE_PROJECTION,
    ORTHOGRAPHIC_PROJECTION
};

struct ProjectionInfo{
    Matrix4 projection;
    float FOV = ToRadians(60.0f);
    float ortho_size = 3.0;
    Matrix4(*projection_function)(float,float ,float ,float, float);
};

struct ViewFrustum{
    Plane3 front;
    Plane3 left;
    Plane3 right;
    Plane3 back;
    Plane3 top;
    Plane3 bottom;
};

class Camera : public Object{
    public:
        Camera(Camera_Projection camera_projection = Camera_Projection::ORTHOGRAPHIC_PROJECTION);
        //Sets the camera to desired position
        const Matrix4& SetCameraPos(const Vector3& pos);
        //Sets the camera direction (looking at) direction
        const Matrix4& SetCameraDir(const Vector3& dir);
        //Moves the camera from current position to the desired position
        const Matrix4& MoveCameraPos(const Vector3& pos);
        //Build the camera matrix given the position and front vectors
        void BuildMat();
        //Build the projection matrix
        void BuildProj();
        //Build view frustum info
        void BuildFrustum();
        //The update method for updating the matrix information
        void Update() override;
        //Returns the view matrix
        const Matrix4& View() const;
        //Returns the projection matrix of the camera
        const Matrix4& Projection() const;
        //Returns the VP (View Projection) matrix already multiplied, to be used with a model matrix
        const Matrix4& ViewProjection() const;
        //Returns the current position
        const Vector3& Pos() const;
        //Returns the up vector of the camera
        const Vector3& Up() const;
        //Returns the front vector of the camera
        const Vector3& Front() const;
        //Returns the projection info of the camera
        const ProjectionInfo& ProjInfo() const;
        const ViewFrustum& Frustum() const;

        float near_plane;
        float far_plane;
        
    private:
        ViewFrustum frustum;
        Matrix4 view;
        Matrix4 view_projection;
        ProjectionInfo proj_info;
        Vector3 camera_pos;
        Vector3 camera_front;
        Vector3 camera_up;
};