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
        //variable that holds the objects used by game_objects and components
        static std::vector<Object*> objects;
        static void AddObjectBack(Object* obj);
        //seperating objects - except components,and game object themselves, since they are gameobject specific - pointers by their name, they will hold the all_object addresses
        virtual void UnloadObject(){};
    private:
        static unsigned int objects_count;
};