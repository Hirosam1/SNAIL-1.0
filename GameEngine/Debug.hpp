#pragma once
#include "GMpch.hpp"

enum ErrorType{
    TEXTURE_IMG_LOAD_FAIL,
    SHADER_COMPILE_FAIL,
    SHADER_LINK_FAIL,
    FILE_LOAD_TEXT_FAIL,
    OBJECTLOADER_LOADING_SCENE_FAIL
};

namespace Debug{
    // void WriteErrorLog(std::string location,std::string line);
    void WriteErrorLog(ErrorType err, const std::string* params, unsigned int size = 0);
    void CleanErrorLog();
}