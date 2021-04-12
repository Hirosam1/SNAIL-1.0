#pragma once
#include "GMpch.hpp"

//An object are group of resources data, with specific methods to be used in components.
class Object {
    public:
        virtual ~Object() = default;
        std::string object_name = "new object";
};