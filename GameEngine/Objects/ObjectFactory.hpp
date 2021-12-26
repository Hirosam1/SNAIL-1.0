#pragma once
#include "GMpch.hpp"

#include "DataStructures/Vector.hpp"
#include "Components/Transform.hpp"

#include "json/json.hpp"

#include "ResourcesMetaData.hpp"


//This file will be responsible for creating all objects used in the game, it also stores the meta-data of the objects that are build in the ResourceLoader funcrtion from 
// the DataManager.hpp 
// !! I might move this "meta-data" from this file to a separate file, that both DataManager and ObjectFactory can reference them from, for better UML, and avoid reference conflicts !!

class Component;
class Resource;
class Object;

class Model;
class Shader;
class Texture;

class Mesh;
class SpriteAtlas;

class ComponentFactory{
    public:
    ComponentFactory();
    static Component* CreateBehavior(nlohmann::json j, const std::string& file_name, std::vector<Object*>* game_objects);
    static Component* CreateCamera(nlohmann::json j, const std::string& file_name, std::vector<Object*>* game_objects);
    static Component* CreateSpriteRenderer(nlohmann::json j,const std::string& file_name, std::vector<Object*>* game_objects);
    static Component* CreateMeshRenderer(nlohmann::json j,const std::string& file_name, std::vector<Object*>* game_objects);
    static Component* CreateSpriteBatchRenderer(nlohmann::json j,const std::string& file_name, std::vector<Object*>* game_objects);
    static Component* CreateSpriteAnimationController(nlohmann::json j,const std::string& file_name, std::vector<Object*>* game_objects);
    static Transform CreateTransform(nlohmann::json j,const std::string& file_name);
    
    //Map that handles the Creation of the components, based on string and function pointer
    std::map<std::string, Component*(*)(nlohmann::json,const std::string&, std::vector<Object*>*)> components_factories;

    static ComponentFactory* singleton;
};

