#pragma once
#include "GMpch.hpp"
#include "Matrix.hpp" 
#include "Matrix_Transform.hpp"
#include "Vector.hpp"
#include "Math.hpp"
#include "Component.hpp"

class GameObject;

class Transform : public Component{
    public:
        //Creates a transform with the default parameters
        Transform();
        //Create a transform with the given paramters
        Transform(const Vector3& pos, const Vector3& rot, const Vector3& scale);
        //Sets the transform position
        void SetPos(const Vector3& pos);
        //Moves from current position to the move position
        Vector3 MovePos(const Vector3& move_pos);
        //Sets the rotation of the transform
        void SetRot(const Vector3& rot);
        //Sets the scale of the transform
        void SetScale(const Vector3& pos);
        //Adds rotation to the current rotation, carefull with gimbal lock!!
        void AddRot(const Vector3& rot);
        //Returns the current position
        const Vector3& Pos() const;
        //Returns the current rotation
        const Vector3& Rot() const;
        //Returns the current Scale
        const Vector3& Scale() const;
        //Returns the model matrix
        const Matrix4& ModelMat() const;
        void Update(GameObject* game_object) override;
        //Gets the front position vector
        Vector3 Front() const;
    private:
        //Updates the matrix values, based on scale, rotation and translation in the correct order
        void BuildMat();
        Matrix4 model_mat;
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

};