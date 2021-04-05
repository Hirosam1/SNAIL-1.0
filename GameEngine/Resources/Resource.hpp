#pragma once
#include "GMpch.hpp"

class Resource{
    public:
        std::string resource_name = "Resource Object";
        //Unloads the resourse from the openGL context
        virtual void UnloadResourse() = 0;
};