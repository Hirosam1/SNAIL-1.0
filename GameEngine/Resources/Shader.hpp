#pragma once
#include "GMpch.hpp"

#include <glad/glad.h>

#include "FileIO.hpp"

//Shader class to perform openGL shader operations
class Shader{
    public:
        Shader(std::string vertex_path, std::string fragment_path);
        //Uses the shader. Use this before any shader operations
        void UseShader();
        //Set uniform for vec3
        void SetUniform3f(const std::string& uniform_name, float a, float b, float c);
        //Set uniform for vec4
        void SetUniform4f(const std::string& uniform_name, float a, float b, float c,float d);
        //Set uniform for int
        void SetUniform1i(const std::string& uniform_name, int a);
        //Set uniform for float
        void SetUniform1f(const std::string& uniform_name, float a);
        //Set uniform for mat4
        void SetUniformMatrix4f(const std::string& uniform_name, const float* mat_ptr);
    private:
        GLuint program_id;  
        GLuint LoadShader(GLenum shader_type, std::string& shader_path);

};