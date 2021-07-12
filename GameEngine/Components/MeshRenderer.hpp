#pragma once
#include "GMpch.hpp"

#include "Components/Renderer.hpp"

class Shader;
class Matrix4;

//Prepare mesh to be renderer, using its shaders and textures, culling faces, and frustum culling
//Needs mesh to render
class MeshRenderer : public Renderer{
    public:
        MeshRenderer(Mesh* mesh, Shader* shader) : Renderer(mesh,shader){}
        void Draw(const Matrix4& MVP, const Shader& shader) override;
    private:
};