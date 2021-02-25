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
int Sprite::draw_count = 0;
void Sprite::Draw(Transform* transform){
    //transform.SetScale(sprite_scale * transform.Scale());
    Transform trans = Transform(transform->Pos(),transform->Rot(),transform->Scale() * sprite_scale);
    Camera* main_camera = *Window::main_window->main_camera;
    Matrix4 MVP = (main_camera->ViewProjection() * trans.ModelMat());
    if(/*TestAABBAgainstFrustum(trans,MVP)*/ true){
        shader->SetUniformMatrix4f(model_str, trans.ModelMat().GetPtr());
        shader->SetUniform4f(atlas_str,tex_coord.x,tex_coord.y,tex_coord.z,tex_coord.w);
        shader->SetUniformMatrix4f(MVP_str, MVP.GetPtr());
        //Chooses the winding order based on the scale
        glFrontFace(trans.Scale().x * trans.Scale().y > 0 ? GL_CCW : GL_CW );
        Sprite::draw_count++;
        sprite_model->Draw(*shader);
    }

    
}

//This could be a function inherited from a parent class called "renderer"
bool Sprite::TestAABBAgainstFrustum(const Transform& tranform, const Matrix4& MVP){
    Camera* main_camera = *Window::main_window->main_camera;
    ImplicitVolumes::AABB aabb = {Vector3(-0.5,-0.5,0.0),Vector3(0.5,0.5,0.0)};
    Vector4 corners[4] = {Vector4(aabb.min.x,aabb.min.y,aabb.min.z,1.0),
                            Vector4(aabb.min.x,aabb.max.y,aabb.min.z,1.0),
                            Vector4(aabb.max.x,aabb.min.y,aabb.min.z,1.0),
                            Vector4(aabb.max.x,aabb.max.y,aabb.min.z,1.0)
                        };
        Vector4 outer_corner;
        for(int i = 0; i < 4; i++){
            Vector4 corner = corners[i]* MVP;
            // if(corner.x < corner.w && corner.x > -corner.w && corner.y < corner.w && corner.y > -corner.w && corner.z < corner.w && corner.z >0){std::cout<<"NOT CULLED|"<<corner<<"\n";return true;}

            if(abs(corner.x) < corner.w && abs(corner.y) < corner.w && (corner.z < corner.w && corner.z > 0)){std::cout<<"NOT CULLED|"<<corner<<"\n"; return true;}
            outer_corner = corner;
        }
        std::cout<<"CULLED|xX"<<outer_corner<<"Xx|\n";
        return false;
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