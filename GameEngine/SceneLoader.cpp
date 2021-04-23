#include "SceneLoader.hpp"

//All includes but scene
#include "DataStructures/Vector.hpp"
#include "DataStructures/Matrix.hpp"
#include "DataStructures/ImplicitObjects.hpp"
#include "DataStructures/Quaternion.hpp"

#include "Math/Math.hpp"
#include "Math/Matrix_Transform.hpp"
#include "Math/Quternion_Transform.hpp"

#include "Objects/Object.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/SpriteAtlas.hpp"

#include "Components/Camera.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Renderer.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Components/Transform.hpp"

#include "Resources/Model.hpp"
#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"
//------------------------------------------
// Behaviour -------------------------------
#include "../MyFiles/include/Behaviours.hpp"

void SceneLoader::LoadResources(const std::string& resources_path){
        //Creating models-----------------------------------------------------
        Model* square_model = new Model(DefaultShapes::SquareWithTex());
        Model* cube_model = new Model(DefaultShapes::CubeWithTex());
        Resource::all_objects[0] = dynamic_cast<Resource*>(square_model);
        Resource::all_objects[1] = dynamic_cast<Resource*>(cube_model);
        //--------------------------------------------------------------------
        Texture* sprite_sheet = new Texture("resources/images/sprite_sheet.png");
        Texture* omni_sprite = new Texture("resources/images/omnipothead.png");
        Texture* follow_sprite = new Texture("resources/images/spooky.png");
        Resource::all_objects[2] = dynamic_cast<Resource*>(sprite_sheet);
        Resource::all_objects[3] = dynamic_cast<Resource*>(omni_sprite);
        //--------------------------------------------------------------------
        Shader* atlas_shader = new Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/sprite.frag");
        Shader* mesh_shader = new Shader ("resources/shaders/vertex/basic.vert","resources/shaders/fragment/sprite.frag");
        Resource::all_objects[4] = dynamic_cast<Resource*>(atlas_shader);
        Resource::all_objects[5] = dynamic_cast<Resource*>(mesh_shader);
        SpriteAtlas* sprite_atlas = new SpriteAtlas(sprite_sheet,1,3);
        Object::all_objects[6] = dynamic_cast<Object*>(sprite_atlas);
        //--------------------------------------------------------------------
        Object::all_objects[7] = dynamic_cast<Object*>(new Mesh(square_model,sprite_sheet));
        Object::all_objects[8] = dynamic_cast<Object*>(new Mesh(square_model,omni_sprite));
        Object::all_objects[9] = dynamic_cast<Object*>(new Mesh(cube_model,follow_sprite));
}

SceneData SceneLoader::LoadScene(const std::string& scene_path){
        GameObject* go = new GameObject();
        SceneData init_scene;
        go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::all_objects[7]), dynamic_cast<Shader*>(Object::all_objects[4]),dynamic_cast<SpriteAtlas*>(Object::all_objects[6] ),0,0));
        go->object_name = "first tile floor";
        go->transform->SetPos(Vector3(0.0,0.5,0.0));
        init_scene.AddGameObject(go);

        go = new GameObject();
        go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::all_objects[7]), dynamic_cast<Shader*>(Object::all_objects[4]),dynamic_cast<SpriteAtlas*>(Object::all_objects[6] ),0,0));
        go->transform->SetPos(Vector3(1.0,0.5,0.0));
        init_scene.AddGameObject(go);

        go = new GameObject();
        go->PushComponentBack(new SpriteRenderer(dynamic_cast<Mesh*>(Object::all_objects[7]), dynamic_cast<Shader*>(Object::all_objects[4]),dynamic_cast<SpriteAtlas*>(Object::all_objects[6]),1,0));
        go->PushComponentBack(new MovingObject());
        go->transform = new Transform(Vector3(-1.5,0.5,0.5),Vector3(0.0,Math::ToRadians(90),0.0),Vector3(1.0,1.0,1.0));
        init_scene.AddGameObject(go);

        go = new GameObject();
        go->object_name = "Camera Follower";
        go->PushComponentBack(new MeshRenderer(dynamic_cast<Mesh*>(Object::all_objects[8]),dynamic_cast<Shader*>(Object::all_objects[5])));
        go->PushComponentBack(new ObjectFollower());
        go->transform->SetPos(Vector3(0.0,1.5,0.5));
        init_scene.AddGameObject(go);

        go = new GameObject();
        go->PushComponentBack(new MeshRenderer(dynamic_cast<Mesh*>(Object::all_objects[9]),dynamic_cast<Shader*>(Object::all_objects[5])));
        //go->PushComponentBack(new HeadFollower());
        go->PushComponentBack(new RotateCubeQuat());
        go->transform->position = Vector3(0.0,1.5,0.5);
        init_scene.AddGameObject(go);


        //Camera has to be added last to avoid weird de-sync rendering
        go = new GameObject();
        go->object_name = "Main Camera";
        go->transform->SetPos(Vector3(0.0,1.0,5.0));
        //Creates a camera and sets up projection configuration
        Camera* a_camera = new Camera(Camera_Projection::PERSPECTIVE_PROJECTION);
        go->PushComponentBack(a_camera);
        go->PushComponentBack(new CameraMovement());
        init_scene.main_camera = a_camera; 
        init_scene.AddGameObject(go);

        return init_scene;
}