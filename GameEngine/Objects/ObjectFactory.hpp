#pragma once
#include "GMpch.hpp"

#include "DataStructures/Vector.hpp"
#include "Components/Transform.hpp"

#include "json/json.hpp"

class Component;
class Resource;


class Model;
class Shader;
class Texture;

class Mesh;
class SpriteAtlas;


class ComponentFactory{
    public:
    ComponentFactory();
    static Component* CreateBehavior(nlohmann::json j, const std::string& file_name);
    static Component* CreateCamera(nlohmann::json j, const std::string& file_name);
    static Component* CreateSpriteRenderer(nlohmann::json j,const std::string& file_name);
    static Component* CreateMeshRenderer(nlohmann::json j,const std::string& file_name);
    static Transform CreateTransform(nlohmann::json j,const std::string& file_name);
    //Map that handles the Creation of the components, based on string and function pointer
    std::map<std::string, Component*(*)(nlohmann::json,const std::string&)> components_factories;

    static ComponentFactory* singleton;
};

class ResourcesInfo{
    public:
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

    static Shader* FindOrCreateShader(const std::string& name);
    static Texture* FindOrCreateTexture(const std::string& name);
    static Model* FindOrCreateModel(const std::string& name);
    
};

class ObjectsInfo{
    public:
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

    static SpriteAtlas* FindOrCreateSpriteAtlas(const std::string& name);
    static Mesh* FindOrCreateMesh(const std::string& name);
};