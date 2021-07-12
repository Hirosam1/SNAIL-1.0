#pragma once
#include "GMpch.hpp"

#include "Components/Renderer.hpp"
#include "Components/Transform.hpp"

#include "Objects/SpriteAtlas.hpp"

#include "DataStructures/Vector.hpp"

class Mesh;

//!!!  Might consider changing this to SpriteRenderer?? !!!!
class SpriteRenderer : public Renderer{
    public:
        //I really dont think I should be passing the model in the sprite constructor! Neighther the Texture! or maaybe yes?
        SpriteRenderer(Mesh* mesh, Shader* shader);
        SpriteRenderer(Mesh* mesh, Shader* shader,SpriteAtlas* sprite_atlas, unsigned int x_coord, unsigned int y_coord);
        //Sets the coordinates of the atlas, "x" sets the horizontal element, "y" selects the vertical element. If you have given the sprite a Sprite Atlas it will set up the normalized coordinates to send to the shader
        void SetAtlasCoordinate(const Vector2& coords);
        //Returns constant value of the Sprite Atlas coordinates, currently set
        const Vector2& AtlasCoords() const;
        void Draw(const Matrix4& transform, const Shader& shader) override;
        //Will update the transform to ajust to sprite dimensions
        Transform BuildTransform(const Transform& transform) const override;
        Vector3 SpriteScale();
        //Optional Sprite atlas
        SpriteAtlas* sprite_atlas = nullptr;
    private:
        //The scale format of the sprite so it does not deform when dealing with non square sprites
        Vector3 sprite_scale;
        //Coordinates for the atlas texture, will be mapped to tex_coords
        Vector2 atlas_coords;
        //Texture Coordinate to the texture sprite atlas
        Vector4 tex_coord;
        //Atlas uniform string
        const std::string atlas_str = "altas_coord";
};