#include "Resources/Shader.hpp"


Logger Shader::log = Logger("Shader");

Shader::Shader(std::string vertex_path, std::string fragment_path){
    int sucess;
    char info_log[512];

    program_id = glCreateProgram();
    GLuint vertex_shader, fragment_shader;

    vertex_shader = LoadShader(GL_VERTEX_SHADER,vertex_path);
    fragment_shader = LoadShader(GL_FRAGMENT_SHADER,fragment_path);

    glAttachShader(program_id,vertex_shader);
    glAttachShader(program_id,fragment_shader);
    glLinkProgram(program_id);
    glGetProgramiv(program_id,GL_LINK_STATUS,&sucess);
    if(!sucess){
        glad_glGetProgramInfoLog(program_id,512,NULL,info_log);
        #ifdef DEBUG
        std::cout<<"ERROR while linking two shaders ("<<vertex_path<<", "<<fragment_path<<")\n\tInfoLog->"<<info_log<<"\n";
        #endif
        log.LogError("Error while linking two shaders ("+vertex_path+", "+fragment_path+")\n\tInfoLog-> "+info_log+".");
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

}


Shader::Shader(std::string vertex_path, std::string geometry_path, std::string fragment_path){
    int sucess;
    char info_log[512];

    program_id = glCreateProgram();
    GLuint vertex_shader, fragment_shader,geometry_shader;

    vertex_shader = LoadShader(GL_VERTEX_SHADER,vertex_path);
    fragment_shader = LoadShader(GL_FRAGMENT_SHADER,fragment_path);
    geometry_shader = LoadShader(GL_GEOMETRY_SHADER,geometry_path);

    glAttachShader(program_id,vertex_shader);
    glAttachShader(program_id,geometry_shader);
    glAttachShader(program_id,fragment_shader);
    glLinkProgram(program_id);
    glGetProgramiv(program_id,GL_LINK_STATUS,&sucess);
    if(!sucess){
        glad_glGetProgramInfoLog(program_id,512,NULL,info_log);
        #ifdef DEBUG
        std::cout<<"ERROR while linking two shaders ("<<vertex_path<<", "<<fragment_path<<")\n\tInfoLog->"<<info_log<<"\n";
        #endif
        log.LogError("Error while linking two shaders ("+vertex_path+", "+fragment_path+")\n\tInfoLog-> "+info_log+".");
    }

    glDeleteShader(geometry_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

GLuint Shader::LoadShader(GLenum shader_type,std::string& shader_path){
    int sucess;
    char info_log[512];

    GLuint shader = glCreateShader(shader_type);
    std::string shader_string = FileIO::ReadFromFile(shader_path);
    const char* c_str = shader_string.data();
    glShaderSource(shader,1,&c_str,NULL);
    glCompileShader(shader);
    glGetShaderiv(shader,GL_COMPILE_STATUS,&sucess);
    if(!sucess){
        glGetShaderInfoLog(shader,512,NULL,info_log);
        #ifdef DEBUG
        std::cout<<"ERROR while compiling shader (" <<shader_path<<")\n\tInfoLog-> " <<info_log<<"\n";
        #endif
        log.LogError("Error while compiling shader ("+shader_path+")\n\tInfoLog-> "+info_log +".");
    }

    return shader;
}

void Shader::UseShader(){
    StateManager::state_manager->UseProgram(program_id);
}

void Shader::SetUniform3f(const std::string& uniform_name, float a, float b, float c) const{
    GLuint loc = glGetUniformLocation(program_id,uniform_name.data());
    glUniform3f(loc,a,b,c);
}

void Shader::SetUniform4f(const std::string& uniform_name, float a, float b, float c,float d) const{
    GLuint loc = glGetUniformLocation(program_id,uniform_name.data());
    glUniform4f(loc,a,b,c,d);  
    
}

void Shader::SetUniform1i(const std::string& uniform_name, int a) const{
    GLuint loc = glGetUniformLocation(program_id,uniform_name.data());
    glUniform1i(loc,a);  
    
}

void Shader::SetUniform1f(const std::string& uniform_name, float a) const{
    GLuint loc = glGetUniformLocation(program_id,uniform_name.data());
    glUniform1f(loc,a); 
}

void Shader::SetUniformMatrix4f(const std::string& uniform_name, const float* mat_ptr) const{
    GLuint loc = glGetUniformLocation(program_id,uniform_name.data());
    glUniformMatrix4fv(loc,1,GL_FALSE,mat_ptr); 
}