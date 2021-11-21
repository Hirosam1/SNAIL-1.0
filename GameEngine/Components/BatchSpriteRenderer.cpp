#include "BatchSpriteRenderer.hpp"

BatchSpriteRenderer::BatchSpriteRenderer(SpriteAtlas* sprite_atlas, Shader* shader): Renderer(nullptr, shader), sprite_atlas(sprite_atlas), texture(sprite_atlas->texture){
    use_frustum_culling= false;
    //Generate a buffer for the Vertex Buffer Object and Element Buffer
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    //Generate a buffer for the Vertex Array Object
    glGenVertexArrays(1,&VAO);

    //Remember, we can bind the VBO BEFORE the binding of the VAO
    StateManager::state_manager->BindsVBO(VBO);
    StateManager::state_manager->BindsVAO(VAO);
    //then we Bind the Element Buffer Object, this HAS to be after 
    StateManager::state_manager->BindsEBO(EBO);

    for(int last_index = 0 ; last_index < max_models; last_index+=4){
        indices.push_back(0+last_index);
        indices.push_back(1+last_index);
        indices.push_back(3+last_index);

        indices.push_back(2+last_index);
        indices.push_back(0+last_index);
        indices.push_back(3+last_index);
    }

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*2*max_models,&indices[0],GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER,sizeof(SpriteBatchData)*max_models,nullptr,GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(SpriteBatchData),(void*)offsetof(SpriteBatchData,pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,false,sizeof(SpriteBatchData),(void*)offsetof(SpriteBatchData,tex_coords));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,4,GL_FLOAT,false,sizeof(SpriteBatchData),(void*)offsetof(SpriteBatchData,atlas_pos));
    glEnableVertexAttribArray(2);
}

int BatchSpriteRenderer::AddSprite(Vector3 pos,int texture_index, Vector2 atlas_coords){
    Vector4 atlas_maped_coords = this->sprite_atlas->GetCoordinate(atlas_coords);
    SpriteBatch sb;
    sb.atlas_coords = atlas_maped_coords;
    sb.pos = pos;
    sb.texture_index = texture_index;
    sprites_batches.push_back(sb);
    return sprites_batches.size();
}

void BatchSpriteRenderer::UpdateSpritePos(int index,Vector3 pos){
    SpriteBatch sp = sprites_batches[index];
    sp.pos = pos;
}


void BatchSpriteRenderer::GenerateGeometry(){
    for(int i = 0; i < sprites_batches.size(); i++){
        GenerateSprite(sprites_batches[i]);
    }
}

void BatchSpriteRenderer::GenerateSprite(SpriteBatch sp){
    SpriteBatchData sbd[4];
    int last_index = indices[indices.size()-1];
    sbd[0].pos.x = sprite_model.vertex_data[0].pos.x + sp.pos.x;
    sbd[0].pos.y = sprite_model.vertex_data[0].pos.y + sp.pos.y;
    sbd[0].pos.z = sp.pos.z;
    sbd[0].tex_coords = sprite_model.vertex_data[0].tex_coords;
    sbd[0].atlas_pos = sp.atlas_coords;

    sbd[1].pos.x = sprite_model.vertex_data[1].pos.x + sp.pos.x;
    sbd[1].pos.y = sprite_model.vertex_data[1].pos.y + sp.pos.y;
    sbd[1].pos.z = sp.pos.z;
    sbd[1].tex_coords = sprite_model.vertex_data[1].tex_coords;
    sbd[1].atlas_pos = sp.atlas_coords;

    sbd[2].pos.x = sprite_model.vertex_data[2].pos.x + sp.pos.x;
    sbd[2].pos.y = sprite_model.vertex_data[2].pos.y + sp.pos.y;
    sbd[2].pos.z = sp.pos.z;
    sbd[2].tex_coords = sprite_model.vertex_data[2].tex_coords;
    sbd[2].atlas_pos = sp.atlas_coords;

    sbd[3].pos.x = sprite_model.vertex_data[3].pos.x + sp.pos.x;
    sbd[3].pos.y = sprite_model.vertex_data[3].pos.y + sp.pos.y;
    sbd[3].pos.z = sp.pos.z;
    sbd[3].tex_coords = sprite_model.vertex_data[3].tex_coords;
    sbd[3].atlas_pos = sp.atlas_coords;

    sprite_data.push_back(sbd[0]);
    sprite_data.push_back(sbd[1]);
    sprite_data.push_back(sbd[2]);
    sprite_data.push_back(sbd[3]);

    //sprites are ordered in fours

}

void BatchSpriteRenderer::UpdateData(){
    StateManager::state_manager->BindsVBO(VBO);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(SpriteBatchData)*sprite_data.size(),&sprite_data[0]);
}

void BatchSpriteRenderer::Draw(const Matrix4& transform, const Shader& shader){
    StateManager::state_manager->BindsVAO(VAO);
    this->UpdateData();
    texture->UseTexture(shader,"Texture1",0);
    shader.SetUniformMatrix4f("MVP",transform.GetPtr());
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
}