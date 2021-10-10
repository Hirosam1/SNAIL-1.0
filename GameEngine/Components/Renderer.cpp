#include "Components/Renderer.hpp"

int Renderer::draw_count = 0;

Transform Renderer::BuildTransform(const Transform& transform) const{
    return Transform(transform);
}

void Renderer::LateUpdate(GameObject* game_object){
    Transform new_transform = BuildTransform(*game_object->transform);
    if(!use_frustum_culling || TestSphereAgainstFrustum(new_transform)){
        Camera* main_camera = Scene::active_scene->main_camera;
        Matrix4 MVP = (main_camera->ViewProjection() * new_transform.ModelMat());
        shader->UseShader();
        //Chooses the winding order based on the scale
        glFrontFace(new_transform.Scale().x * new_transform.Scale().y * new_transform.Scale().z > 0 ? GL_CCW : GL_CW );
        draw_count++;
        //Delegates to sub-class
        Draw(MVP,*shader);
        //Back to normal the winding order
        glFrontFace(GL_CCW);
    }
}

bool Renderer::TestSphereAgainstFrustum(const Transform& transform) const{
    Camera* main_camera = Scene::active_scene->main_camera;
    float diagonal = Math::qsqrt(transform.Scale().x*transform.Scale().x + transform.Scale().y*transform.Scale().y);
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