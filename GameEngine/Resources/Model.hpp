#pragma once
#include "GMpch.hpp"
#include "Resources/Resource.hpp"
#include "Resources/Shader.hpp"

#include "GLHandler/GLStateManager.hpp"

#include  "DataStructures/Vector.hpp"
#include "DataStructures/Matrix.hpp"

struct VertexData{
    Vector3 pos;
    Vector2 tex_coords;
};

//Data structure reserved for sprite batches, it stores they position as well the atlas position
struct SpriteBatchData{
    Vector3 pos;
    Vector2 tex_coords;
    Vector4 atlas_pos;
};

struct ModelData
{
    std::vector<VertexData> vertex_data;
    std::vector<GLuint> indices;
};

//Creates a model with vertex data to be sent to the GPU
class Model : public Resource{
    public:
        //Model(std::vector<VertexData> vertex_data) : vertex_data(vertex_data){SetUpBuffer();};
        Model(ModelData model_data){SetUpBuffer(model_data);};
        unsigned int indices_size, vertices_size;
        //Draws the model using arrays or elements depending of model parameters
        void Draw(const Shader* shader,const Matrix4& MVP_mat);
        //Updates index data with SubBufferData. However cannot increase its size.
        //void UpdateIndices();
        //Updates Vertex data with SubBufferData. However cannot increase its size.
        //void UpdateVertices();
        //Binds VAO 
        void BindVAO();
        //Unloads the resourse from the openGL context
        void UnloadObject() override{glDeleteBuffers(1,&VBO); glDeleteBuffers(1,&EBO); glDeleteVertexArrays(1,&VAO); VBO = 0; EBO = 0; VAO = 0;};
    private:
        bool has_indices;
        //Method for glDrawArrays
        void DrawArrays();
        //Method for glDrawElements
        void DrawElements();
        //Set up all buffer elements such as VBO,VAO and EBO, also buffers data
        void SetUpBuffer(ModelData model_data);
        GLuint VBO = 0;
        GLuint EBO = 0;
        GLuint VAO = 0;
        //MVP uniform string
        const std::string MVP_str = "MVP";
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