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
    default:
        ErrorText = "Unknon Error ->" + params[0];
        break;
    }
    outfile << ErrorText << "\n";
    outfile.close();
}