#pragma once
#include "GMpch.hpp"
#include "Resources/Texture.hpp"
#include "GMpch.hpp"
#include "Components/Transform.hpp"
#include "Vector.hpp"

class SpriteAtlas{
    public:
        SpriteAtlas(Texture* texture,unsigned int vertical_count, unsigned int horizontal_count);
        //Returns the beginning and end of the tex coordinates
        Vector4 GetCoordinate(Vector2 tex);
        Texture* texture;
        //The vertical count of images in the image atlas
        unsigned int vertical_count;
        //The horizontal count of images in the image atlas
        unsigned int horizontal_count;
        //The scale of each image, used by the sprite
        Vector3 sprite_scale;
    private:
        //Vertical and horizontal tex-coordindte step
        float vertical_step;
        float horizontal_step;
};