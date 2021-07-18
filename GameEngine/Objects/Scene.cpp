#include "Scene.hpp"
#include "DataManager.hpp"

Scene* Scene::active_scene = nullptr;

Scene::Scene(const std::string& scene_path){
    SceneData scene_data = ObjectLoader::LoadScene(scene_path);
    scene_name = scene_data.scene_name;
    game_objects = scene_data.game_objects;
    objects = scene_data.objects;
    main_camera = scene_data.main_camera;
    std::cout<<"OBJECTS SIZE--> "<< this->objects.size() <<"\n";
}

void Scene::BeginScene(){
    for(GameObject* game_object : game_objects){
        game_object->Begin();
    }
}

void Scene::UpdateScene(){
    for(GameObject* game_object : game_objects){
        if(game_object){
            game_object->Update();
        }
    }
    if(this->request_change){
        this->UnloadScene();
        Scene::active_scene = this->my_next_scene;
        Scene::active_scene->BeginScene();
        delete this;
        return;
    }
}

GameObject* Scene::FindGameObject(const std::string& object_name){
    for(GameObject* game_object : game_objects){
        if(strcmp(game_object->object_name.data(),object_name.data()) == 0){
            return game_object;
        }
    }
    return nullptr;
}

void Scene::AddGameObject(GameObject* game_object){
    game_objects.push_back(game_object);
}

std::list<GameObject*>& Scene::GameObjectList(){
    return game_objects;
}

void Scene::LoadScene(const std::string& scene_path){
    Scene::active_scene->my_next_scene = new Scene(scene_path);
    Scene::active_scene->request_change = true;
}

void Scene::UnloadScene(){
    for(GameObject* go : game_objects){
        go->UnloadObject();
        delete go;
    }
    for(int i = 0; i < objects.size(); i++){
        if(objects[i]){
            objects[i]->UnloadObject();
            delete objects[i];
            objects[i] = nullptr;
        }
    }
}