#pragma once
#include "GMpch.hpp"
#include "Resources/Texture.hpp"
#include "Resources/Model.hpp"
#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "ImplicitObjects.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "Vector.hpp"
#include "Window.hpp"

class MeshRenderer : public Component{
    public:
        MeshRenderer(Model* model, Shader* shader, Texture* texture = nullptr);
        void Update(GameObject* game_object) override;
        void Draw(Transform* transform);
    private:
        Shader* shader;
        Texture* texture;
        Model* model;
        bool TestSphereAgainstFrustum(const Transform& transform) const;
};