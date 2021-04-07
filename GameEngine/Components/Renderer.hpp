#pragma once
#include "Components/Component.hpp"

#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"
#include  "Resources/Shader.hpp"
#include "Resources/Mesh.hpp"

#include "GameObject.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Matrix.hpp"

//Basic abstract renderer, checks for frustum and face culling, then calls the pure virtual function that others renderers implement
class Renderer : public Component{
    public:
        Renderer(Mesh* mesh, Shader* shader) : mesh(mesh),
                                               shader(shader){}
        void Update(GameObject* game_object) override;
    private:
        //Build new Tranform for specific operations, like sprite renderer
        virtual Transform BuildTransform(const Transform& transform) const;
    protected:
        virtual void Draw(const Matrix4& transform, const Shader& shader) = 0;
        //test a sphere in the transform coordinates against the view frustum, returns true if visible
        bool TestSphereAgainstFrustum(const Transform& transform) const;
        // !!! Probably have many meshes each one with its shaders and textures !!!
        Mesh* mesh;
        Shader* shader;
};