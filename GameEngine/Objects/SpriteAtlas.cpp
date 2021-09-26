#include "Objects/SpriteAtlas.hpp"

//This is a small value that determine the border (skin) of the texture coordinates to avoid clipping into the next texture
const float skin_thickness = 0.001;

SpriteAtlas::SpriteAtlas(Texture* texture,unsigned int vertical_count, unsigned int horizontal_count):texture(texture), 
vertical_count(vertical_count), horizontal_count(horizontal_count){
    vertical_step = texture->image_data.height/vertical_count;
    horizontal_step = texture->image_data.width/horizontal_count;
    float aspect_ratio = (float)horizontal_step/(float)vertical_step;
    sprite_scale = Vector3(aspect_ratio,1.0,1.0);
    //Normalize steps
    vertical_step = vertical_step/texture->image_data.height;
    horizontal_step = horizontal_step/texture->image_data.width;
}

Vector4 SpriteAtlas::GetCoordinate(Vector2 tex_coords){
    return Vector4((int)tex_coords.x*horizontal_step+skin_thickness,
                (int)tex_coords.y*vertical_step+skin_thickness,
                ((int)tex_coords.x+1)*horizontal_step-skin_thickness,
                ((int)tex_coords.y+1)*vertical_step-skin_thickness);
}
