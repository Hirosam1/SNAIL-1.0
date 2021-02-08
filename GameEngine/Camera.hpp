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
        //Returns the view matrix
        const Matrix4& View() const;
        //Returns the current position
        const Vector3& Pos() const;
        //Returns the up vector of the camera
        const Vector3& Up() const;
        //Returns the front vector of the camera
        const Vector3& Front() const;
        
    private:
        Matrix4 view;
        Vector3 camera_pos;
        Vector3 camera_front;
        Vector3 camera_up;
};