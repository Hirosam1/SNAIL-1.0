#include "Objects/SpriteAtlas.hpp"

SpriteAtlas::SpriteAtlas(Texture* texture,unsigned int vertical_count, unsigned int horizontal_count):texture(texture), 
vertical_count(vertical_count), horizontal_count(horizontal_count){
    vertical_step = texture->image_data.height/vertical_count;
    horizontal_step = texture->image_data.width/horizontal_count;

    //this->half_pixel_correction_h  = (1.0f/(float)texture->image_data.width)/2.0f;
    //this->half_pixel_correction_v  = (1.0f/(float)texture->image_data.height)/2.0f;

    this->half_pixel_correction_h  = 0.001f;
    this->half_pixel_correction_v  = 0.001f;

    float aspect_ratio = (float)horizontal_step/(float)vertical_step;
    sprite_scale = Vector3(aspect_ratio,1.0,1.0);
    //Normalize steps
    vertical_step = vertical_step/texture->image_data.height;
    horizontal_step = horizontal_step/texture->image_data.width;
}

Vector4 SpriteAtlas::GetCoordinate(Vector2 tex_coords){
    return Vector4((int)tex_coords.x*horizontal_step+this->half_pixel_correction_h,
                (int)tex_coords.y*vertical_step+this->half_pixel_correction_v,
                ((int)tex_coords.x+1)*horizontal_step-this->half_pixel_correction_h,
                ((int)tex_coords.y+1)*vertical_step-this->half_pixel_correction_v);
}
