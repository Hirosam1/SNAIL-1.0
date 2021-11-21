#pragma once
#include "GMpch.hpp"
#include "Components/Renderer.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/SpriteAtlas.hpp"
#include "Resources/Shader.hpp"
#include "Objects/GameObject.hpp"


//Renders a static batch of sprites
class BatchSpriteRenderer : public Renderer{
    public:
        BatchSpriteRenderer(SpriteAtlas* aprite_atlas, Shader* shader);
        //Create a sprite on the batch renderer, and returns its index
        int AddSprite(Vector3 pos = Vector3(),int texture_index = 0, Vector2 atlas_coords = Vector2());
        //After done adding all sprites, generate all geometry
        void GenerateGeometry();
        void UpdateSpritePos(int index,Vector3 pos);

        void Draw(const Matrix4& transform, const Shader& shader) override;
        
        const int max_models = 500;
        Mesh* batch_mesh = nullptr;
        SpriteAtlas* sprite_atlas = nullptr;
        GLuint VBO = 0;
        GLuint EBO = 0;
        GLuint VAO = 0;
    private:
        ~BatchSpriteRenderer();
        //General information  about a sprite batch (a full rectangle with texture and atlas texture)
        struct SpriteBatch
        {
            Vector3 pos;
            int texture_index;
            Vector4 atlas_coords;
        };
        ModelData sprite_model = DefaultShapes::SquareWithTex();
        //Generates and insert new sprite data into sprite_data
        void GenerateSprite(SpriteBatch sp);
        //Each frame updates the  data
        void UpdateData();
        std::vector<SpriteBatch> sprites_batches;
        std::vector<SpriteBatchData> sprite_data;
        std::vector<GLuint> indices;
        Texture* texture;

};