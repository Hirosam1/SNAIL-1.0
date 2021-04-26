#pragma once
#include "GMpch.hpp"

enum ErrorType{
    TEXTURE_IMG_LOAD_FAIL,
    SHADER_COMPILE_FAIL,
    SHADER_LINK_FAIL,
    FILE_LOAD_TEXT_FAIL,
    OBJECTLOADER_LOADING_SCENE_FAIL,
    OBJECTLOADER_NODATA_SCENE_WARN,
    OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL,
    OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL,
    OBJECTLOADER_NO_COMPONENT_FACTOR_FAIL,
    OBJECTLOADER_NO_BEHAVIOR_FAIL
};

namespace Debug{
    // void WriteErrorLog(std::string location,std::string line);
    void WriteErrorLog(ErrorType err, const std::string* params, unsigned int size = 0);
    void CleanErrorLog();
}