#pragma once
#include "GMpch.hpp"

class Resource{
    public:
        std::string resource_name = "Resource Object";
        //Unloads the resourse from the openGL context
        virtual void UnloadResourse(){
            #ifdef DEBUG 
            std::cout<<"IMPLEMENT UNLOADER!!!\n"; 
            #endif
        }
        //Temporary, but real variable that holds all resources from the game
        static Resource* all_resources[];
};