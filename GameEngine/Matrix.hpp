#pragma once
#include "Vector.hpp"
#include "GMpch.hpp"
//Matrix 4x4
struct Matrix4
{
    Matrix4(float identity = 0.0f);
    Matrix4(const Matrix4& mat_c);
    //Multiply element by value the matrix
    Matrix4 Multiply(float a);
    //Multiply element by value the matrix
    Matrix4 operator*(float a);
    //Performs dot product between two matrices
    Matrix4 Dot(const Matrix4& mat) const;
    //Performs dot product between matrix and a vector of similar dimensions
    Vector4 Dot(const Vector4& vec) const;
    //Multiply element by element the two matrix
    Matrix4 operator*(const Matrix4& mat )const;
    //Multiply element by element the two matrix
    Vector4 operator*(const Vector4& vec) const;
    //Gets the n row
    Vector4 Row(int n) const;
    //Gets the n column
    Vector4 Column(int n) const;
    GLfloat mat[16];
    const GLfloat* GetPtr() const;
};

std::ostream& operator<<(std::ostream& stream, const Matrix4& mat);