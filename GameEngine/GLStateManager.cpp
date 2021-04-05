#include "GLStateManager.hpp"

StateManager* StateManager::state_manager = 0;

StateManager::StateManager(){
    if(!StateManager::state_manager){
        StateManager::state_manager = this;
    }
}

bool StateManager::BindsVAO(GLuint vao){
    if(current_VAO != vao){
        glBindVertexArray(vao);
        current_VAO = vao;
        return true;
    }
    return false;
}

bool StateManager::BindsVBO(GLuint vbo){
    if(current_VBO != vbo){
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        current_VBO = vbo;
        return true;
    }
    return false;
}

bool StateManager::BindsEBO(GLuint ebo){
    if(current_EBO != ebo){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
        current_EBO = ebo;
        return true;
    }
    return false;
}

bool StateManager::BindTexture(GLuint texture){
    if(current_texture != texture){
        glBindTexture(GL_TEXTURE_2D,texture);
        current_texture = texture;
        return true;
    }
    return false;
}

bool StateManager::UseProgram(GLuint program){
    if(current_shaderProgram != program){
        glUseProgram(program);
        current_shaderProgram = program;
        return true;
    }
    return false;
}