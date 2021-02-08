#include "Components/Sprite.hpp"

Sprite::Sprite(Model* model, Texture* texture, Shader* a_shader): sprite_model(model), sprite_texture(texture), shader(a_shader){  
    float aspec_ratio = sprite_texture->image_data.width/(float)sprite_texture->image_data.height;
    sprite_scale = Vector3(1.0*aspec_ratio,1.0,1.0);
    //transform.SetScale(sprite_scale);
}

Sprite::Sprite(Model* model, SpriteAtlas* atlas, unsigned int x_coord, unsigned int y_coord, Shader* a_shader) : sprite_model(model), sprite_atlas(atlas), shader(a_shader){
    sprite_scale = sprite_atlas->sprite_scale;
    //transform.SetScale(sprite_atlas->sprite_scale);
    sprite_texture = sprite_atlas->texture;
    atlas_coords = Vector2(x_coord,y_coord);
    tex_coord = sprite_atlas->GetCoordinate(atlas_coords);
}

void Sprite::Draw(Transform* transform){
    //transform.SetScale(sprite_scale * transform.Scale());
    Transform trans = Transform(transform->Pos(),transform->Rot(),transform->Scale() * sprite_scale);
    Camera* main_camera = *Window::main_window->main_camera;
    shader->SetUniformMatrix4f(model_str, trans.ModelMat().GetPtr());
    shader->SetUniform4f(atlas_str,tex_coord.x,tex_coord.y,tex_coord.z,tex_coord.w);
    shader->SetUniformMatrix4f(MVP_str, (main_camera->Projection() * main_camera->View() * trans.ModelMat()).GetPtr());

    //Chooses the winding order based on the scale
    glFrontFace(trans.Scale().x * trans.Scale().y > 0 ? GL_CCW : GL_CW );
    sprite_model->Draw(*shader);
    
}

bool Sprite::FrustumCulling(const Transform& tranform){
    float bigger = tranform.Scale().x > tranform.Scale().y ? tranform.Scale().x : tranform.Scale().y;
    Vector3 direction_frustum = Normalize(-tranform.Pos()) * bigger;
    // return direction_frustum 
}

void Sprite::SetAtlasCoordinate(const Vector2&  atlas_coords){
    this->atlas_coords = atlas_coords;
    if(sprite_atlas != nullptr){
        tex_coord = sprite_atlas->GetCoordinate(atlas_coords);
    }
}

const Vector2& Sprite::AtlasCoords() const{
    return atlas_coords;
}

void Sprite::Update(GameObject* game_object){
    Draw(game_object->transform);
}