#pragma once
#include "GMpch.hpp"

#include "Components/Component.hpp"

#include "DataStructures/Matrix.hpp" 
#include "DataStructures/Vector.hpp"

#include "Math/Matrix_Transform.hpp"
#include "Math/Math.hpp"

#include "DataStructures/Quaternion.hpp"

#include "Math/Quternion_Transform.hpp"

class GameObject;

class Transform : public Component{
    public:
        //Creates a transform with the default parameters
        Transform();
        //Copy transform
        Transform(const Transform& transform) : position(Vector3(transform.Pos())),
                                                rotation(transform.Rot()),
                                                scale(Vector3(transform.Scale())){BuildMat();}
        //Create a transform with the given paramters
        Transform(const Vector3& pos, const Vector3& rot, const Vector3& scale);
        Transform(const Vector3& pos, const Quaternion& rot, const Vector3& scale);
        //Sets the transform position
        void SetPos(const Vector3& pos);
        //Moves from current position to the move position
        Vector3 Translate(const Vector3& move_pos);
        //Sets the rotation of the transform
        void SetRot(const Vector3& rot);
        //Set rotation in Quaternions
        void SetRot(const Quaternion& quat);
        //Sets the scale of the transform
        void SetScale(const Vector3& pos);
        //Adds rotation to the current rotation, carefull with gimbal lock!!
        void Rotate(const Vector3& rot);
        //Adds rotation to the current rotation, using quaternions
        void Rotate(const Quaternion& quat);
        //updates rotation looking at target
        void LookAt(const Vector3& target);
        //Returns the current position
        const Vector3& Pos() const;
        //Returns the current rotation
        const Quaternion& Rot() const;
        //Returns the current Scale
        const Vector3& Scale() const;
        //Returns the model matrix
        const Matrix4& ModelMat() const;
        void Update(GameObject* game_object) override;
        //Gets the front position vector
        Vector3 Front() const;
        //transform position
        Vector3 position;
        //transform rotation
        Quaternion rotation;
        //transform scale
        Vector3 scale;
    private:
        //Updates the matrix values, based on scale, rotation and translation in the correct order
        void BuildMat();
        Matrix4 model_mat;

};