#pragma once
#include "GMpch.hpp"

class StateManager{
    public:
        StateManager();
        static StateManager* state_manager;
        //Binds VAO, returns true if there was a state change, if not it returns false
        bool BindsVAO(GLuint vao);
        //Use Texture, returns true if there was a state change, if not it returns false
        bool BindTexture(GLuint texture);
        //Use Shader, returns true if there was a state change, if not it returns false
        bool UseProgram(GLuint program);

    private:
        GLuint current_VAO =  0 ;
        GLuint current_texture = 0;
        GLuint current_shaderProgram = 0;
};