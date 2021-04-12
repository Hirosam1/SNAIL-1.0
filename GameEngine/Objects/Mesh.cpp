#include "Objects/Mesh.hpp"

Mesh::Mesh(Model* model, Texture* texture) : model(model),
                                             texture(texture){
    
}

void Mesh::Draw(const Shader& shader, const Matrix4& MVP){
    if(texture){
        texture->UseTexture(shader,"Texture1",0);
    }
    model->Draw(&shader,MVP);
}