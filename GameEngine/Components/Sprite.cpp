#include "Components/Sprite.hpp"

Sprite::Sprite(Model* model, Texture* texture, Shader* a_shader): sprite_model(model), sprite_texture(texture), shader(a_shader){  
    float aspec_ratio = sprite_texture->image_data.width/(float)sprite_texture->image_data.height;
    sprite_scale = Vector3(1.0*aspec_ratio,1.0,1.0);
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
    Transform trans = Transform(transform->Pos(),transform->Rot(),transform->Scale() * sprite_scale);
    Camera* main_camera = Window::main_window->main_camera;
    Matrix4 MVP = (main_camera->ViewProjection() * trans.ModelMat());
    //Checks for frustum culling
    if(TestSphereAgainstFrustum(trans)){
        //Chooses the winding order based on the scale
        glFrontFace(trans.Scale().x * trans.Scale().y > 0 ? GL_CCW : GL_CW );
        shader->UseShader();
        shader->SetUniform4f(atlas_str,tex_coord.x,tex_coord.y,tex_coord.z,tex_coord.w);
        //!!! I really shouldn't be setting the uniform name and position here gotta think of something better !!!!
        sprite_texture->UseTexture(*shader,"Texture1",0);
        Sprite::draw_count++;
        sprite_model->Draw(shader,MVP);
    }

    
}

bool Sprite::TestSphereAgainstFrustum(const Transform& transform) const{
    Camera* main_camera = Window::main_window->main_camera;
    float diagonal = qsqrt(transform.Scale().x*transform.Scale().x + transform.Scale().y*transform.Scale().y);
    ImplicitVolumes::Sphere bounding_sphere =  ImplicitVolumes::Sphere{diagonal/2.0f,
                                                                        transform.Pos()};
    ViewFrustum frustum = main_camera->Frustum();
    Plane3* plane = (Plane3*) &frustum;

    for(int i = 0; i < sizeof(frustum); i += sizeof(Plane3)){
        float D = bounding_sphere.position.x * plane->normal.x + bounding_sphere.position.y * plane->normal.y + bounding_sphere.position.z * plane->normal.z + plane->d;
        D += bounding_sphere.radius;
        if(D < 0){
            return false;
        }
        plane++;
    }
    return true;
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