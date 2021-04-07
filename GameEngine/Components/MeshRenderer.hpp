#pragma once
#include "GMpch.hpp"
#include "Resources/Texture.hpp"
#include "Resources/Model.hpp"
#include "Resources/Mesh.hpp"

#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Components/Renderer.hpp"

#include "ImplicitObjects.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "Vector.hpp"
#include "Window.hpp"
#include "GameObject.hpp"
#include "Matrix.hpp"

//Prepare mesh to be renderer, useing its shaders and textures, culling faces, and frustum culling
//Needs mesh to render
class MeshRenderer : public Renderer{
    public:
        MeshRenderer(Mesh* mesh, Shader* shader) : Renderer(mesh,shader){}
        void Draw(const Matrix4& MVP, const Shader& shader) override;
        static int draw_count;
    private:
};