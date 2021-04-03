#pragma once
#include "GMpch.hpp"
#include  "Vector.hpp"
#include "Resources/Shader.hpp"
#include "GLStateManager.hpp"

struct VertexData{
    Vector3 pos;
    Vector2 tex_coords;
};

struct ModelData
{
    std::vector<VertexData> vertex_data;
    std::vector<GLuint> indices;
};

//Creates a model with vertex data to be sent to the GPU
class Model{
    public:
        Model();
        Model(std::vector<VertexData> vertex_data) : vertex_data(vertex_data){SetUpBuffer();};
        Model(ModelData model_data) : vertex_data(model_data.vertex_data), indices(model_data.indices){SetUpBuffer();};
        std::vector<VertexData> vertex_data;
        std::vector<GLuint> indices;
        //Draws the model using arrays or elements depending of model parameters
        void Draw(Shader& shader);
        //Updates index data with SubBufferData. However cannot increase its size.
        void UpdateIndices();
        //Updates Vertex data with SubBufferData. However cannot increase its size.
        void UpdateVertices();
        //Binds VAO 
        void BindVAO();
    private:
        bool has_indices;
        //Method for glDrawArrays
        void DrawArrays(Shader& shader);
        //Method for glDrawElements
        void DrawElements(Shader& shader);
        //Set up all buffer elemts such as VBO,VAO and EBO, also buffers data
        void SetUpBuffer();
        GLuint VBO = 0;
        GLuint VAO = 0;
        GLuint EBO = 0;
};
//Default Shapes with vertex data
namespace DefaultShapes{
    //Creates a 2D circle gives radius and vertives. The more Vertices the closer to a circle it gets
    ModelData Circle(float radius, unsigned int vertices);
    //Creates a 3D cube with texture coordinates
    ModelData CubeWithTex();
    //Creates a 2D circle with texture coordinates
    ModelData SquareWithTex();
}