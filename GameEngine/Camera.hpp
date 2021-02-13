#pragma once
#include "GMpch.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Math.hpp"
#include "Matrix_Transform.hpp"
#include "Window.hpp"
#include "Object.hpp"

enum Camera_Projection{
    PERSPECTIVE_PROJECTION,
    ORTHOGRAPHIC_PROJECTION
};

struct ProjectionInfo{
    Matrix4 projection;
    float FOV = ToRadians(90.0f);
    float ortho_size = 3.0;
    Matrix4(*projection_function)(float,float ,float ,float, float);
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
        //The update method for updating the matrix information
        void Update() override;
        //Returns the view matrix
        const Matrix4& View() const;
        //Returns the projection matrix of the camera
        const Matrix4& Projection() const;
        //Returns the current position
        const Vector3& Pos() const;
        //Returns the up vector of the camera
        const Vector3& Up() const;
        //Returns the front vector of the camera
        const Vector3& Front() const;
        //Returns the projection info of the camera
        const ProjectionInfo& ProjInfo() const;
        float near_plane;
        float far_plane;
        
    private:
        Matrix4 view;
        ProjectionInfo proj_info;
        Vector3 camera_pos;
        Vector3 camera_front;
        Vector3 camera_up;
};