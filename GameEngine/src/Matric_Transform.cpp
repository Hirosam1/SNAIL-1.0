#include "Matrix_Transform.hpp"

using namespace Projection;

Matrix4 Projection::Perspective(float FOV, float aspec_ratio, float near, float far, float ortho_size){
    Matrix4 projection(1.0f);
    float tangent = tanf(FOV/2); //half of FOV
    float height = tangent * near; //half height of near plane, based on the FOV
    float width = height * aspec_ratio; //width proportional of the aspec_ratio
    projection.mat[0] = near/width;
    projection.mat[1*4+1] = near/height;
    projection.mat[2*4+2] = -(far+near)/(far-near);
    projection.mat[2*4+3] = -1.0f;
    projection.mat[3*4+2] = -(2.0f*far*near)/(far-near);
    projection.mat[15] = 0.0f;
    return projection;
}

Matrix4 Projection::Orthographic(float FOV, float aspec_ratio, float near, float far, float ortho_size){
    Matrix4 projection(1.0f);
    float height = ortho_size;
    float width = height * aspec_ratio; //width proportional of the aspec_ratio
    projection.mat[0] = 1/width;
    projection.mat[1*4+1] = 1/height;
    projection.mat[2*4+2] = - 2/(far-near);
    projection.mat[3*4+2] = -(far+near)/(far-near);
    projection.mat[3*4+3] = 1;

    return projection;
}