#pragma once
#include "GMpch.hpp"

class Object {
    public:
        std::string object_name = "new object";
        virtual void Begin(){};
        virtual void Update(){};
};