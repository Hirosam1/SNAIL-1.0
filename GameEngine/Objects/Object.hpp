#pragma once
#include "GMpch.hpp"

//Pure Objects forwards declarations
class Mesh;
class Scene;
class SpriteAtlas;
//Resources forwards declarion
class Model;
class Resource;
class Shader;
class Texture;

//An object are group of resources data, with specific methods to be used in components.
class Object{
    public:
        virtual ~Object() = default;
        std::string object_name = "new object";
        virtual void UnloadObject(){};
};