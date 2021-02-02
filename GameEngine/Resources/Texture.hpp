#pragma once
#include "GMpch.hpp"

#include<glad/glad.h>
#include "Debug.hpp"
#include "ImageLoading/stb_image.h"
#include "Resources/Shader.hpp"


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

class Texture{
    public:
        Texture(std::string texture_path, bool repeat = true);
        void UseTexture(Shader& shader,std::string& uniform_name, int tex_num);
        ImageIO::ImageData image_data;
    private:
        GLuint texture_id;
};
