#pragma once
#include "GMpch.hpp"

#include "Objects/Object.hpp"

#include "Resources/Texture.hpp"

#include "DataStructures/Vector.hpp"

class SpriteAtlas : public Object{
    public:
        SpriteAtlas(Texture* texture,unsigned int vertical_count, unsigned int horizontal_count);
        //Returns the beginning and end of the tex coordinates in normalized coordinates
        Vector4 GetCoordinate(Vector2 tex);
        Texture* texture;
        //The vertical count of images in the image atlas
        int vertical_count;
        //The horizontal count of images in the image atlas
        int horizontal_count;
        //The scale of each image, used by the sprite
        Vector3 sprite_scale;
    private:
        //Vertical and horizontal tex-coordinate step
        float vertical_step;
        float horizontal_step;
        float half_pixel_correction_v = 0.0f;
        float half_pixel_correction_h = 0.0f;
};