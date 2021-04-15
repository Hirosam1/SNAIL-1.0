#pragma once
#include "GMpch.hpp"

#include "DataStructures/Matrix.hpp"
#include "DataStructures/Vector.hpp"

#include "Math/Math.hpp"

namespace Transformation{
    //Extracts euler rotation from matrix, matrix must be not scaled
    inline Vector3 ExtractEulerFromMat(const Matrix4& mat){
        float x,y,z;
        x = atan2(mat.Row(2).y,mat.Row(2).z);
        float cosY = sqrt(mat.Row(0).x*mat.Row(0).x + mat.Row(1).x *mat.Row(1).x);
        y = atan2(-mat.Row(2).x,cosY);
        float cosX = cos(x);
        float sinX = sin(x);
        float sinZ = sinX * mat.Row(0).z - cosX * mat.Row(0).y;
        float cosZ = cosX * mat.Row(1).y - sinX * mat.Row(1).z;
        z = atan2(sinZ,cosZ);
        //Invert values, it seems to be clockwise instead of counter clockwise
        return Vector3(-x,-y,-z);
    }
    
    //Translates the matrix given position, will apply transformation before given matrix
    inline Matrix4 Translate(const Matrix4& mat, const Vector3& trans_pos){
        Matrix4 translation = Matrix4(1.0);
        translation.mat[12] = trans_pos.x;
        translation.mat[13] = trans_pos.y;
        translation.mat[14] = trans_pos.z;
        return mat * translation;
    }
    //Scale the matrix given scale, will apply transformation before given matrix
    inline Matrix4 Scale(const Matrix4& mat, const Vector3& scale){
        Matrix4 scaleble = Matrix4(1.0);
        scaleble.mat[0] = scale.x;
        scaleble.mat[5] = scale.y;
        scaleble.mat[10]= scale.z;
        return mat * scaleble;
    }
    //Rotates the matrix given axis and angle, will apply transformation before given matrix
    inline Matrix4 Rotate(const Matrix4& mat,float rot_rad ,const Vector3& rot_axis){
        Matrix4 rotation = Matrix4(1.0);
        float cos_rot = cos(rot_rad);
        float sin_rot = sin(rot_rad);
        rotation.mat[0] = cos_rot+(rot_axis.x*rot_axis.x)*(1-cos_rot);
        rotation.mat[1] = rot_axis.y*rot_axis.x*(1-cos_rot)+rot_axis.z*sin_rot;
        rotation.mat[2] = rot_axis.z*rot_axis.x*(1-cos_rot)-rot_axis.y*sin_rot;
        rotation.mat[3] = 0;
        rotation.mat[4] = rot_axis.x*rot_axis.y*(1-cos_rot)-rot_axis.z*sin_rot;
        rotation.mat[5] = cos_rot+(rot_axis.y*rot_axis.y)*(1-cos_rot);
        rotation.mat[6] = rot_axis.z*rot_axis.y*(1-cos_rot)+rot_axis.x*sin_rot;
        rotation.mat[7] = 0;
        rotation.mat[8] = rot_axis.x*rot_axis.z*(1-cos_rot)+rot_axis.y*sin_rot;
        rotation.mat[9] = rot_axis.y*rot_axis.z*(1-cos_rot)-rot_axis.x*sin_rot;
        rotation.mat[10] = cos_rot+(rot_axis.z*rot_axis.z)*(1-cos_rot);
        return mat * rotation;
    }

    //Rotates the matrix in the X vector, will apply transformation before given matrix
    inline Matrix4 RotateX(const Matrix4& mat, float rot_rad){
        Matrix4 rotation = Matrix4(1.0f);
        float cos_rot = cos(rot_rad);
        float sin_rot = sin(rot_rad);
        rotation.mat[5] = cos_rot;
        rotation.mat[9] = -sin_rot;
        rotation.mat[6] = sin_rot;
        rotation.mat[10] = cos_rot;
        return mat * rotation;
    }
    //Inverse of rotateX
    inline Matrix4 RotateXInv(const Matrix4& mat, float rot_rad){
        Matrix4 rotation = Matrix4(1.0f);
        float cos_rot = cos(rot_rad);
        float sin_rot = sin(rot_rad);
        rotation.mat[5] = cos_rot;
        rotation.mat[6] = -sin_rot;
        rotation.mat[9] = sin_rot;
        rotation.mat[10] = cos_rot;
        return mat * rotation;
    }

    //Rotates the matrix in the Y vector, will apply transformation before given matrix
    inline Matrix4 RotateY(const Matrix4& mat, float rot_rad){
        Matrix4 rotation = Matrix4(1.0f);
        float cos_rot = cos(rot_rad);
        float sin_rot = sin(rot_rad);
        rotation.mat[0] = cos_rot;
        rotation.mat[8] = sin_rot;
        rotation.mat[2] = -sin_rot;
        rotation.mat[10]= cos_rot;
        return mat * rotation;
    }
    //Inverse of rotate Y
    inline Matrix4 RotateYInv(const Matrix4& mat, float rot_rad){
        Matrix4 rotation = Matrix4(1.0f);
        float cos_rot = cos(rot_rad);
        float sin_rot = sin(rot_rad);
        rotation.mat[0] = cos_rot;
        rotation.mat[2] = sin_rot;
        rotation.mat[8] = -sin_rot;
        rotation.mat[10]= cos_rot;
        return mat * rotation;
    }

    //Rotates the matrix in the Z vector, will apply transformation before given matrix
    inline Matrix4 RotateZ(const Matrix4& mat, float rot_rad){
        Matrix4 rotation = Matrix4(1.0f);
        float cos_rot = cos(rot_rad);
        float sin_rot = sin(rot_rad);
        rotation.mat[0] = cos_rot;
        rotation.mat[4] = -sin_rot;
        rotation.mat[1] = sin_rot;
        rotation.mat[5] = cos_rot;
        return mat * rotation;

    }
    //Inverse of rotateZ
    inline Matrix4 RotateZInv(const Matrix4& mat, float rot_rad){
        Matrix4 rotation = Matrix4(1.0f);
        float cos_rot = cos(rot_rad);
        float sin_rot = sin(rot_rad);
        rotation.mat[0] = cos_rot;
        rotation.mat[1] = -sin_rot;
        rotation.mat[4] = sin_rot;
        rotation.mat[5] = cos_rot;
        return mat * rotation;
    }

    //Creates a matrix transformation that is the inverse of look at, usefull for camera look at
    inline Matrix4 CamLookAt(Vector3 pos, Vector3 target, Vector3 up){
        Matrix4 look(1.0);
        Vector3 z_axis = Math::Normalize(pos - target);
        Vector3 x_axis = Math::Normalize(up.Cross(z_axis));
        Vector3 y_axis = z_axis.Cross(x_axis);

        look.mat[0] = x_axis.x;
        look.mat[4] = x_axis.y;
        look.mat[8] = x_axis.z;

        look.mat[1] = y_axis.x;
        look.mat[5] = y_axis.y;
        look.mat[9] = y_axis.z;

        look.mat[2] = z_axis.x;
        look.mat[6] = z_axis.y;
        look.mat[10]= z_axis.z;

        look.mat[12] = -x_axis.Dot(pos);
        look.mat[13] = -y_axis.Dot(pos);
        look.mat[14] = -z_axis.Dot(pos);

        return look;

    }
    //Creates a matrix transformation that looks at target
    inline Matrix4 LookAt(Vector3 pos, Vector3 target, Vector3 up){
        Matrix4 look(1.0);
        Vector3 z_axis = Math::Normalize(target - pos);
        Vector3 x_axis = Math::Normalize(up.Cross(z_axis));
        Vector3 y_axis = z_axis.Cross(x_axis);

        look.mat[0] = x_axis.x;
        look.mat[1] = x_axis.y;
        look.mat[2] = x_axis.z;

        look.mat[4] = y_axis.x;
        look.mat[5] = y_axis.y;
        look.mat[6] = y_axis.z;

        look.mat[8] = z_axis.x;
        look.mat[9] = z_axis.y;
        look.mat[10]= z_axis.z;

        look.mat[12] = pos.x;
        look.mat[13] = pos.y;
        look.mat[14] = pos.z;

        return look;
    }

}

namespace Projection{
    //Creates a perspective matrix given the FOV, aspect ratio near and far plane.
    Matrix4 Perspective(float FOV, float aspec_ratio, float near, float far, float ortho_size = 0);
    //Creates an orthographic matrix given the aspect ratio, the orthographic size of view, near and far planes
    Matrix4 Orthographic(float FOV, float aspec_ratio, float near, float far, float ortho_size);
}