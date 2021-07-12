#include "Scene.hpp"
#include "DataManager.hpp"

Scene* Scene::active_scene = nullptr;

Scene::Scene(const std::string& scene_path){
    SceneData scene_data = ObjectLoader::LoadScene(scene_path);
    game_objects = scene_data.game_objects;
    main_camera = scene_data.main_camera;
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

void Scene::UnloadScene(){
    for(GameObject* game_object : game_objects){
        if(game_object){
            game_object->UnloadObject();
        }
    }
    ResourcesInfo::shaders_map.
}