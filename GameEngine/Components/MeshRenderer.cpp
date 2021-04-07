#include "Components/MeshRenderer.hpp"

int MeshRenderer::draw_count = 0;

void MeshRenderer::Draw(const Matrix4& MVP, const Shader& shader){
        MeshRenderer::draw_count++;
        mesh->Draw(shader,MVP);
}