#include "Components/MeshRenderer.hpp"

void MeshRenderer::Draw(const Matrix4& MVP, const Shader& shader){
        mesh->Draw(shader,MVP);
}