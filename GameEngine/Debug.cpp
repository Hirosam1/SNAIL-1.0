#include "Debug.hpp"


const char ErrorLog[] = "ErrorLog.log";
void Debug::CleanErrorLog(){
    std::ofstream outfile;
    outfile.open(ErrorLog, std::ofstream::out | std::ofstream::trunc);
    outfile.close();
}

// void Debug::WriteErrorLog(std::string location,std::string line){
//     std::ofstream outfile;
//     outfile.open(ErrorLog, std::ofstream::out | std::ofstream::app);
//     outfile <<location<<"(" <<line << ")\n";
//     outfile.close();
// }

void Debug::WriteErrorLog(ErrorType err, const std::string* params, unsigned int size){
    std::ofstream outfile;
    outfile.open(ErrorLog, std::ofstream::out | std::ofstream::app);
    std::string ErrorText;
    switch (err)
    {
    case ErrorType::TEXTURE_IMG_LOAD_FAIL:
        ErrorText = "ERROR::@Texture::TEXTURE_IMG_LOAD_FAIL(Failed to load the "+params[0]+" texture. Check file name/extension.)";
        break;
    case ErrorType::SHADER_COMPILE_FAIL:
        ErrorText = "ERROR::@Shader::SHADER_COMPILE_FAIL(Error while compiling shader ("+params[0]+")\n\tInfoLog-> "+ params[1];
        break;
    case ErrorType::SHADER_LINK_FAIL:
        ErrorText = "ERROR::@Shader::SHADER_LINK_FAIL(Error while linking two shaders ("+params[0]+", "+params[1]+")\n\tInfoLog-> "+params[2];
        break;
    case ErrorType::FILE_LOAD_TEXT_FAIL:
        ErrorText = "ERROR::@FileIO::FILE_LOAD_TEXT_FAIL(File "+params[0]+" was not successfully opened!";
        break;
    case ErrorType::OBJECTLOADER_LOADING_SCENE_FAIL:
        ErrorText = "ERROR::@ObjectLoader::OBJECTLOADER_LOADING_SCENE_FAIL(Failed to load the " + params[0] +" scene file, check the name/extension.)";
        break;
    case ErrorType::OBJECTLOADER_NODATA_SCENE_WARN:
        ErrorText = "WARNING::@ObjectLoader::OBJECTLOADER_NODATA_SCENE_WARN(The file " + params[0] + " does not have any game_object data, the scene will be completely empty!)";
        break;
    case ErrorType::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL:
        ErrorText = "ERROR::@ObjectLoader::OBJECTLOADER_OBJECT_DATA_MISMATCH_FAIL(From the scene "+ params[0] +" the object "+ params[1] +" created on resources does not exist, or does not match type.)";
        break;
    case ErrorType::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL:
        ErrorText = "ERROR::@ObjectLoader::OBJECTLOADER_COMPONENT_BAD_PARAM_FAIL(From the scene "+ params[0] +" is passing bad/few paramters to component " + params[1] + ".)";
        break;
    case ErrorType::OBJECTLOADER_NO_COMPONENT_FACTOR_FAIL:
        ErrorText = "ERROR::@ObjectLoader::OBJECTLOADER_NO_COMPONENT_FACTOR_FAIL(From the scene "+ params[0] +" there are no factories to build component "+ params[1]  +".)";
        break;
    case ErrorType::OBJECTLOADER_NO_BEHAVIOR_FAIL:
        ErrorText = "ERROR::@ObjectLoader::OBJECTLOADER_NO_BEHAVIOR_FAIL(From the scene" + params[0] +" there is no behavior named "+ params[1] +".)";
        break;
    default:
        ErrorText = "Unknon Error ->" + params[0];
        break;
    }
    outfile << ErrorText << "\n";
    outfile.close();
}