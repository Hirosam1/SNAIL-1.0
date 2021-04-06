#include "Resources/Model.hpp"

Model::Model(){
    vertex_data = std::vector<VertexData>();
    indices = std::vector<GLuint>();
}

void Model::SetUpBuffer(){
    has_indices = false;
    //Generate a buffer for the Vertex Buffer Object and Element Buffer
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    //Generate a buffer for the Vertex Array Object
    glGenVertexArrays(1,&VAO);
    //!!Remember!! we can bind the VBO BEFORE the binding of the VAO
    StateManager::state_manager->BindsVBO(VBO);
    StateManager::state_manager->BindsVAO(VAO);
    //then we Bind the Element Buffer Object, this HAS to be after 
    StateManager::state_manager->BindsEBO(EBO);    
    // //now we buffer (store) the data for the elment and array buffers. It Copies the values to the buffer memory
    if(indices.size() > 1){
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*indices.size(),&indices[0],GL_STATIC_DRAW);
        has_indices = true;
    }
    glBufferData(GL_ARRAY_BUFFER,sizeof(VertexData) * vertex_data.size(),&vertex_data[0],GL_STATIC_DRAW);
    //Linking vertex Attributes. This will tell openGl how to read our array buffer data.
    //This state WILL be stored
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexData),(void*)offsetof(VertexData,pos));
    //We will enable the attributes indexes we want to use. That will ALSO be stored in the VAO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(VertexData),(void*)offsetof(VertexData,tex_coords));
    glEnableVertexAttribArray(1);

    //Unbind Thingss------------------------------------------------------
    StateManager::state_manager->BindsVAO(0);
    StateManager::state_manager->BindsVAO(0);
    StateManager::state_manager->BindsEBO(0);  
}

void Model::Draw(const Shader* shader, const Matrix4& MVP_mat){
    if(VAO){
        shader->SetUniformMatrix4f(MVP_str, MVP_mat.GetPtr());
        StateManager::state_manager->BindsVAO(VAO);
        if(has_indices){
            DrawElements();
        }else{
            DrawArrays();
        }
    }
}

void Model::DrawArrays(){
    glDrawArrays(GL_TRIANGLES,0,vertex_data.size());
}


void Model::DrawElements(){
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
}

void Model::UpdateIndices(){
    StateManager::state_manager->BindsEBO(EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,sizeof(GLuint)*indices.size(),&indices[0] );
    StateManager::state_manager->BindsEBO(0);
}

void Model::UpdateVertices(){
    StateManager::state_manager->BindsVBO(VBO);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(VertexData)*vertex_data.size(),&vertex_data[0]);
    StateManager::state_manager->BindsEBO(0);
}

void Model::BindVAO(){
    StateManager::state_manager->BindsVAO(VAO);
}

//default shapes======================
#pragma region


ModelData DefaultShapes::CubeWithTex(){
    std::vector<VertexData> vertex_data = std::vector<VertexData>();
    //Back
    vertex_data.push_back(VertexData{Vector3(-0.5f, -0.5f, -0.5f),Vector2(1.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, -0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, -0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, -0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, -0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, -0.5f),Vector2(.0f, 1.0f)});
    //Top V
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, -0.5f),Vector2(0.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, 0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, -0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, 0.5f),Vector2(1.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, -0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, 0.5f),Vector2(0.0f, 0.0f)});
    //Front V
    vertex_data.push_back(VertexData{Vector3(-0.5f, -0.5f, 0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, 0.5f),Vector2(1.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, 0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, 0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, 0.5f),Vector2(0.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, -0.5f, 0.5f),Vector2(0.0f, 0.0f)});
    //Left V
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, 0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, -0.5f),Vector2(0.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, -0.5f, 0.5f),Vector2(1.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, 0.5f, 0.5f),Vector2(1.0f, 1.0f)});
    //Right V
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, 0.5f),Vector2(0.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, 0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, -0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, 0.5f, -0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, 0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, -0.5f),Vector2(1.0f, 0.0f)});
    //Bottom V
    vertex_data.push_back(VertexData{Vector3(-0.5f,-0.5f, -0.5f),Vector2(0.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, -0.5f),Vector2(1.0f, 0.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, 0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(0.5f, -0.5f, 0.5f),Vector2(1.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, -0.5f, 0.5f),Vector2(0.0f, 1.0f)});
    vertex_data.push_back(VertexData{Vector3(-0.5f, -0.5f, -0.5f),Vector2(0.0f, 0.0f)});

    return ModelData{vertex_data};
}

ModelData DefaultShapes::SquareWithTex(){
    std::vector<VertexData> vertex_data = std::vector<VertexData>();
    vertex_data.push_back(VertexData{Vector3(-.5f,-.5f,0.0f), Vector2(0.0f,0.0f)});
    vertex_data.push_back(VertexData{Vector3(.5f,-.5f,0.0f), Vector2(1.0f,0.0f)});
    vertex_data.push_back(VertexData{Vector3(-.5f,.5f,0.0f), Vector2(0.0f,1.0f)});
    vertex_data.push_back(VertexData{Vector3(.5f,0.5f,0.0f), Vector2(1.0f,1.0f)});

    std::vector<GLuint> indices = std::vector<GLuint>();
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(3);

    return ModelData {vertex_data, indices};
}


#pragma endregion