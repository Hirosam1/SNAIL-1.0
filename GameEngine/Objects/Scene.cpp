#include "Scene.hpp"

Scene* Scene::active_scene = nullptr;

Scene::Scene(const std::string& scene_path){
}

void Scene::BeginScene(){
    for(GameObject* game_object : game_objects){
        game_object->Begin();
    }
}

void Scene::UpdateScene(){
    for(GameObject* game_object : game_objects){
        game_object->Update();
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