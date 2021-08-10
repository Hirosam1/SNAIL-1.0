#pragma once
#include "Components/Component.hpp"

#include "Resources/Shader.hpp"

#include "Components/Camera.hpp"

#include "Objects/GameObject.hpp"
#include "Objects/Scene.hpp"
#include "Objects/Mesh.hpp"

#include "DataStructures/Matrix.hpp"
#include "DataStructures/ImplicitObjects.hpp"

class Texture;

//Basic abstract renderer, checks for frustum and face culling, then calls the pure virtual function that others renderers implement
class Renderer : public Component{
    public:
        Renderer(Mesh* mesh, Shader* shader) : mesh(mesh),
                                               shader(shader){}
        void Update(GameObject* go){}
        void LateUpdate(GameObject* game_object) override;
        // !!! Probably have many meshes each one with its shaders and textures !!!
        Mesh* mesh;
        Shader* shader;
        //Draw count in the last frame
        static int draw_count;
    private:
        //test a sphere in the transform coordinates against the view frustum, returns true if visible
        bool TestSphereAgainstFrustum(const Transform& transform) const;
    protected:
        //Build new Tranform for specific operations, like sprite renderer
        virtual Transform BuildTransform(const Transform& transform) const;
        virtual void Draw(const Matrix4& transform, const Shader& shader) = 0;
};