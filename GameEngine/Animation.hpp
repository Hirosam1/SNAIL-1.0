
#pragma once

#include "GMpch.hpp"
#include "DataStructures/Vector.hpp"


struct Animation{
    struct AnimationKey{
        //Time to wait after the last key
        float wait_time;
        Vector2 atlas_pos;
    };
    std::string name;
    std::vector<AnimationKey> animation_keys;
};
