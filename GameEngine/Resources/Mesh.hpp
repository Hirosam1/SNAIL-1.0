#pragma once
#include "Components/Component.hpp"
#include "Components/Transform.hpp"

#include "Resources/Model.hpp"
#include "Resources/Texture.hpp"

#include "Camera.hpp"
#include "Matrix.hpp"
#include "GameObject.hpp"

//This class cannot know about the mesh renderer

//This has geometrical and texture information about a mesh
class Mesh : public Resource{
    public:
        // !!! maybe I can make to default add a default texture !!! 
        Mesh(Model* model, Texture* texture = nullptr);
        void Draw(const Shader& shader, const Matrix4& MVP);
        //Model to be rendered
        Model* model;
        //Texture of the model
        Texture* texture;
    private:
        //Internal tranform for more dynamic rendering like non square sprites
        Transform internal_transform;
};