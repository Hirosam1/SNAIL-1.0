#pragma once
#include "GMpch.hpp"
#include "Resources/Texture.hpp"
#include "Resources/Model.hpp"
#include "Resources/Shader.hpp"
#include "Resources/SpriteAtlas.hpp"
#include "Vector.hpp"
#include "Components/Component.hpp"
#include "GameObject.hpp"
#include "Components/Transform.hpp"

class Sprite : public Component{
    public:
        //I really dont think I should be passing the model in the sprite constructor! Neighther the Texture! or maaybe yes?
        Sprite(Model* model, Texture* texture, Shader* a_shader = nullptr);
        Sprite(Model* mdel, SpriteAtlas* sprite_atlas, unsigned int x_coord, unsigned int y_coord, Shader* a_shader = nullptr);
        //Sets the coordinates of the atlas, "x" sets the horizontal element, "y" selects the vertical element. If you have given the sprite a
        //Sprite Atplas it will set up the normalized coordinates to send to the shader
        void SetAtlasCoordinate(const Vector2& coords);
        //Returns constant value of the Sprite Atlas coordinates, currently set
        const Vector2& AtlasCoords() const;
        //Draw the sprite
        void Draw(Transform* transform);
        //Update method override to be called from the GameObject
        void Update(GameObject* game_object) override;
        //Texture to the sprite to be sent to GPU
        Texture* sprite_texture = nullptr;
        //Optional Sprite atlas
        SpriteAtlas* sprite_atlas = nullptr;
        //Shader to use
        Shader* shader;
        std::string tex1_str = "Texture1";
        std::string model_str = "model";
        std::string atlas_str = "altas_coord";
        
    private:
        //The scale format of the sprite so it does not deform when dealing with non square sprites
        Vector3 sprite_scale;
        Vector2 atlas_coords;
        Model* sprite_model;
        //Texture Coordinate to the sprite atlas
        Vector4 tex_coord;
        
};