#pragma once

#include "Objects/Object.hpp"

#include "Resources/Model.hpp"
#include "Resources/Texture.hpp"

#include "Components/Transform.hpp"

class Texture;
class Shader;

//This has geometrical and texture information about a mesh
class Mesh : public Object{
    public:
        // !!! maybe I can make to default add a default texture !!! 
        Mesh(Model* model, Texture* texture = nullptr);
        void Draw(const Shader& shader, const Matrix4& MVP);
        ~Mesh(){std::cout<<"tried to delete mesh\n";}
        //Model to be rendered
        Model* model;
        //Texture of the model
        Texture* texture;
    private:
        //Internal tranform for more dynamic rendering like non square sprites
        Transform internal_transform;
};