#pragma once
#include "GMpch.hpp"

#include "Objects/Object.hpp"

#include "Resources/Texture.hpp"

#include "DataStructures/Vector.hpp"

class SpriteAtlas : public Object{
    public:
        SpriteAtlas(Texture* texture,unsigned int vertical_count, unsigned int horizontal_count);
        ~SpriteAtlas(){std::cout<<"tried to delete sprite atlas\n";}
        //Returns the beginning and end of the tex coordinates in normalized coordinates
        Vector4 GetCoordinate(Vector2 tex);
        Texture* texture;
        //The vertical count of images in the image atlas
        unsigned int vertical_count;
        //The horizontal count of images in the image atlas
        unsigned int horizontal_count;
        //The scale of each image, used by the sprite
        Vector3 sprite_scale;
    private:
        //Vertical and horizontal tex-coordinate step
        float vertical_step;
        float horizontal_step;
};