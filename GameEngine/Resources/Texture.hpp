#pragma once
#include "GMpch.hpp"
#include<glad/glad.h>

#include "Resources/Resource.hpp"

#include "Debug.hpp"
#include "ImageLoading/stb_image.h"

#include "Resources/Shader.hpp"

#include "GLStateManager.hpp"


namespace ImageIO{

    struct ImageData{
        int width;
        int height;
        int nChannels;
        unsigned char *data;
    };
    inline ImageData LoadImage(std::string& path);

    inline void FreeImageData(ImageData& img_data);

}

class Texture : public Resource{
    public:
        Texture(std::string texture_path, bool repeat = true);
        void UseTexture(const Shader& shader,const std::string& uniform_name, int tex_num) const;
        ImageIO::ImageData image_data;
        //Unloads the resourse from the openGL context
        void UnloadResourse() override{glDeleteTextures(1,&texture_id);}
        ~Texture(){}
    private:
        GLuint texture_id;
};
