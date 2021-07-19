#include "Components/SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(Mesh* mesh, Shader* shader): Renderer(mesh,shader){  
    // float aspec_ratio = mesh->texture->image_data.width/(float)mesh->texture->image_data.height;
    sprite_scale = mesh->texture->image_data.width > mesh->texture->image_data.height?
                    Vector3(mesh->texture->image_data.width/(float)mesh->texture->image_data.height,1.0,1.0) :
                    Vector3(1.0,mesh->texture->image_data.height/(float) mesh->texture->image_data.width,1.0);
    object_name = "SpriteRenderer";
}

SpriteRenderer::SpriteRenderer(Mesh* mesh, Shader* shader,SpriteAtlas* atlas, unsigned int x_coord, unsigned int y_coord) : Renderer(mesh,shader),sprite_atlas(atlas){
    sprite_scale = sprite_atlas->sprite_scale;
    atlas_coords = Vector2(x_coord,y_coord);
    tex_coord = sprite_atlas->GetCoordinate(atlas_coords);
}

void SpriteRenderer::Draw(const Matrix4& MVP, const Shader& shader){
    shader.SetUniform4f(atlas_str,tex_coord.x,tex_coord.y,tex_coord.z,tex_coord.w);
    mesh->Draw(shader,MVP);
}

Vector3 SpriteRenderer::SpriteScale(){
    return sprite_scale;
}


Transform SpriteRenderer::BuildTransform(const Transform& transform) const{
    return Transform(transform.position,transform.rotation,transform.scale * sprite_scale);
}

void SpriteRenderer::SetAtlasCoordinate(const Vector2&  atlas_coords){
    this->atlas_coords = atlas_coords;
    if(sprite_atlas){
        tex_coord = sprite_atlas->GetCoordinate(atlas_coords);
    }
}

const Vector2& SpriteRenderer::AtlasCoords() const{
    return atlas_coords;
}
