#pragma once
#include "GMpch.hpp"

#include "DataStructures/Vector.hpp"
#include "Components/Transform.hpp"

#include "json/json.hpp"

class Component;

namespace ComponentFactory{
    Component* CreateBehavior(nlohmann::json j, const std::string& file_name);
    Component* CreateCamera(nlohmann::json j, const std::string& file_name);
    Component* CreateSpriteRenderer(nlohmann::json j,const std::string& file_name);
    //Map that handles the Creation of the components, based on string and function pointer
    static std::map<std::string, Component*(*)(nlohmann::json,const std::string&)> components_factories =   {      
        {"SpriteRenderer", CreateSpriteRenderer},
        {"Camera", CreateCamera},
        {"Behavior", CreateBehavior},
    };
    Transform CreateTransform(nlohmann::json j,const std::string& file_name);
};

namespace ResourceFactory{
    
};