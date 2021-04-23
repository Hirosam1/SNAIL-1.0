#pragma once
#include "GMpch.hpp"
#include "Objects/Object.hpp"

class Resource : public Object{
    public:
        std::string resource_name = "Resource Object";
        //Unloads the resourse from the openGL context
        void UnloadObject() override{
            #ifdef DEBUG 
            std::cout<<"IMPLEMENT RESOURCE UNLOADER!!!\n"; 
            #endif
        }
};