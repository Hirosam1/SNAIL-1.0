#pragma once
#include"GMpch.hpp"

#include <glad/glad.h>

class Matrix4;
//Vector4 Holds 4 values. And have operations between the same vector-type
struct Vector4{
        public:
            Vector4(){x = 0.0f; y = 0.0f; z = 0.0f; a=0;};
            Vector4(float x,float y,float z, float w) : x (x), y(y),z(z),w(w){};
            void SetValues(float x,float y,float z,float w);
            Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w){};
            void operator=(const Vector4 other){this->x = other.x;this->y = other.y;this->z = other.z; this->w=other.w;};
            union{
                struct{GLfloat x,y,z,w;};
                struct{GLfloat r,g,b,a;};
            };
        
        Vector4 Add(const Vector4& other)const;
        Vector4 Add(float val)const;
        Vector4 operator+(const Vector4& other)const;
        Vector4 operator+(const float val)const;

        Vector4 Subtract(const Vector4& other)const;
        Vector4 Subtract(const float val)const;
        Vector4 operator-(const Vector4& other)const;
        Vector4 operator-(const float val)const;

        Vector4 Multiply(const Vector4& other)const;
        Vector4 Multiply(const float val)const;
        Vector4 Dot(const Matrix4& matrix) const;
        Vector4 operator*(const Vector4& other) const;
        Vector4 operator*(const float val) const;
        Vector4 operator*(const Matrix4& matrix) const;

        Vector4 Divide(const float val) const;
        Vector4 operator/(const float val) const;

        float Dot(const Vector4& other) const;
        //friend std::ostream& operator<<(std::ostream&, const MathS::Vector4&);
        //Linear interpolation
        Vector4 Lerp(const Vector4& end, float t) const;

        bool operator==(const Vector4& other) const;
        bool operator!=(const Vector4& other) const;

    };

//Vector3 Holds 3 values. And have operations between the same vector-type
struct Vector3{
        public:
            Vector3(){x = 0.0f; y = 0.0f; z = 0.0f;};
            Vector3(float x,float y,float z) : x (x), y(y),z(z){};
            void SetValues(float x,float y,float z);
            Vector3 operator=(const Vector3 vec) const{return vec;};
            union{
                struct{GLfloat x,y,z;};
                struct{GLfloat r,g,b;};
            };

        Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z){};
        void operator=(const Vector3& other){this->x = other.x;this->y = other.y;this->z = other.z;};

        Vector3 Add(const Vector3& other)const;
        Vector3 Add(float val)const;
        Vector3 operator+(const Vector3& other)const;
        Vector3 operator+(const float val)const;
        //**implemented others**
        void operator+=(const Vector3& vec);

        Vector3 Subtract(const Vector3& other)const;
        Vector3 Subtract(const float val)const;
        Vector3 operator-(const Vector3& other)const;
        Vector3 operator-(const float val)const;
        //**implemented others**
        void operator-=(const Vector3& vec);

        Vector3 Multiply(const Vector3& other)const;
        Vector3 Multiply(const float val)const;
        Vector3 operator*(const Vector3& other) const;
        Vector3 operator*(const float val) const;

        Vector3 Cross(const Vector3& other) const;

        Vector3 Divide(const float val) const;
        Vector3 operator/(float val) const;

        float Dot(const Vector3& other) const;
        //friend std::ostream& operator<<(std::ostream&, const MathS::Vector3&);
        Vector3 Lerp(const Vector3& end, float t) const;

        bool operator==(const Vector3& other) const;
        bool operator!=(const Vector3& other) const;
        

    };

//Vector2 Holds 2 values. And have operations between the same vector-type
struct Vector2{
        public:
            Vector2(){x = 0.0f; y = 0.0f;};
            Vector2(float x,float y) : x (x), y(y){};
            void SetValues(float x,float y);
            Vector2(const Vector2& other) : x(other.x), y(other.y){};
            void operator=(const Vector2 other){this->x = other.x;this->y = other.y;};
            union{
                struct{GLfloat x,y;};
                struct{GLfloat r,g;};
            };

        Vector2 Add(const Vector2& other)const;
        Vector2 Add(float val)const;
        Vector2 operator+(const Vector2& other)const;
        Vector2 operator+(const float val)const;

        Vector2 Subtract(const Vector2& other)const;
        Vector2 Subtract(const float val)const;
        Vector2 operator-(const Vector2& other)const;
        Vector2 operator-(const float val)const;

        Vector2 Multiply(const Vector2& other)const;
        Vector2 Multiply(const float val)const;
        Vector2 operator*(const Vector2& other) const;
        Vector2 operator*(const float val) const;
        //friend std::ostream& operator<<(std::ostream&, const MathS::Vector2&);

        Vector2 Divide(const float val) const;
        Vector2 operator/(const float val) const;

        Vector2 Rotate(const float angle);

        Vector2 Lerp(const Vector2& end, float t);

        bool operator==(const Vector2& other) const;
        bool operator!=(const Vector2& other) const;
        

    };

    std::ostream& operator<<(std::ostream& stream, const Vector4& other);
    std::ostream& operator<<(std::ostream& stream, const Vector3& other);
    std::ostream& operator<<(std::ostream& stream, const Vector2& other);

    //!!implement others!!
    Vector2 operator*(float a, const Vector2& vec);
    //!!implement others!!
    Vector3 operator-(float a, const Vector3& vec);
    Vector3 operator*(float a, const Vector3& vec);
    Vector3 operator-(const Vector3& vec);
    //!!implement others!!
    Vector4 operator*(float a, const Vector4& vec);
    Vector4 operator-(const Vector4& vec);
    