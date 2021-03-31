#include "Resources/Texture.hpp"
using namespace ImageIO;

inline ImageData ImageIO::LoadImage(std::string& path){
        ImageData img_data{0,0,0,nullptr};
        img_data.data = stbi_load(path.data(), &img_data.width, &img_data.height, &img_data.nChannels, 0);
        return img_data;
    }

inline void ImageIO::FreeImageData(ImageData& img_data){
    stbi_image_free(img_data.data);
    img_data.data = nullptr;
}

Texture::Texture(std::string texture_path, bool repeat){
    stbi_set_flip_vertically_on_load(true);
    image_data = LoadImage(texture_path);
    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D,texture_id);
    //Sets the texture wrap parameter for the R and T tex coords STR(XYZ)
    //Set the bound texture wraping/filtering options
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, repeat? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, repeat? GL_REPEAT : GL_CLAMP_TO_EDGE);
    //Important for the generation of mipmaps
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    if(image_data.data){
        GLuint nChannels = GL_RGB;
        if(image_data.nChannels > 3){
            nChannels = GL_RGBA;
        }
        //now that the texture is bound we can start generating a texture using the previously loaded image data
        glTexImage2D(GL_TEXTURE_2D,0,nChannels,image_data.width,image_data.height,0,nChannels,GL_UNSIGNED_BYTE,image_data.data);
        //Creting this avoids some artifacts
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout<<"Failed to load texture\n";
        Debug::WriteErrorLog("ERROR::Texture","Failed to load the "+texture_path+" texture. Check file name/extension.");
    }
    FreeImageData(image_data);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::UseTexture(Shader& shader,const std::string& uniform_name, int tex_num){
    shader.SetUniform1i(uniform_name,tex_num);
    //Any bindTexture calls after activate will affect the texture unit
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture_id);
}