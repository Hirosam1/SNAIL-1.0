#include "Components/MeshRenderer.hpp"

MeshRenderer::MeshRenderer(Model* model, Shader* shader, Texture* texture) : model(model),
                                                                             shader(shader),
                                                                             texture(texture){
}

void MeshRenderer::Update(GameObject* game_obj){
    Draw(game_obj->transform);
}

int MeshRenderer::draw_count = 0;

void MeshRenderer::Draw(Transform* transform){
    Camera* main_camera = Window::main_window->main_camera;
    Matrix4 MVP = (main_camera->ViewProjection() * transform->ModelMat());
    if(TestSphereAgainstFrustum(*transform)){
        shader->UseShader();
        if(texture){
            texture->UseTexture(*shader,"Texture1",0);
        }
        MeshRenderer::draw_count++;
        model->Draw(shader,MVP);
    }
}
//!! Code repetition!!
bool MeshRenderer::TestSphereAgainstFrustum(const Transform& transform) const{
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