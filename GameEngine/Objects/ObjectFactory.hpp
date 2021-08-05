#pragma once
#include "GMpch.hpp"

#include "DataStructures/Vector.hpp"
#include "Components/Transform.hpp"

#include "json/json.hpp"


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
    static Transform CreateTransform(nlohmann::json j,const std::string& file_name);
    //Map that handles the Creation of the components, based on string and function pointer
    std::map<std::string, Component*(*)(nlohmann::json,const std::string&, std::vector<Object*>*)> components_factories;

    static ComponentFactory* singleton;
};

class ResourcesInfo{
    public:
    static const std::string extension;
    static std::string starting_scene_path;
    ResourcesInfo();
    struct ShaderInfo{
        std::string vertex_path;
        std::string fragment_path;
    };

    struct TextureInfo{
        std::string texture_path;
    };

    struct ModelInfo{
        std::string model_path;
        int default_shape = -1;
    };
    static ResourcesInfo* singleton;

    std::map<std::string, ShaderInfo> shaders_map;
    std::map<std::string, TextureInfo> texture_map;
    std::map<std::string, ModelInfo> model_map;

    static Shader* FindOrLoadShader(const std::string& name, std::vector<Object*>* game_objects);
    static Texture* FindOrLoadTexture(const std::string& name, std::vector<Object*>* game_objects);
    static Model* FindOrLoadModel(const std::string& name, std::vector<Object*>* game_objects);
    
};

class ObjectsInfo{
    public:
    static const std::string extension;
    ObjectsInfo();
    struct SpriteAtlasInfo{
        std::string sheet_texture_name;
        Vector2 atlas_dimensions;
    };
    struct MeshInfo{
        std::string model_name;
        std::string texture_name;
    }; 
    static ObjectsInfo* singleton;

    std::map<std::string, SpriteAtlasInfo> sprite_atlas_map;
    std::map<std::string, MeshInfo> meshes_map;

    static SpriteAtlas* FindOrLoadSpriteAtlas(const std::string& name, std::vector<Object*>* game_objects);
    static Mesh* FindOrLoadMesh(const std::string& name, std::vector<Object*>* game_objects);
};