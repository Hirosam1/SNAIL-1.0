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
        ErrorText = "ERROR::@ObjectLoader::OBJECTLOADER_LOADING_SCENE_FAIL(Failed to load the " + params[0] +" file, check the name/extension.)";
        break;
    case ErrorType::OBJECTLOADER_NO_SCENE_INFO_FAIL:
        ErrorText = "ERROR::@ObjectLoader::OBJECTLOADER_NO_SCENE_INFO_FAIL(There is not enough scene information in file " + params[0] + ")";
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
    case ErrorType::RESLOADER_NO_RESINFO_FAIL:
        ErrorText = "ERROR::@ObjLoader::RESLOADER_NO_RESINFO_FAIL(There is no enough information in resource file " + params[0] + ".)";
        break;
    case ErrorType::NO_ERROR:
        return;
    default:
        ErrorText = "Unknon Error ->" + params[0];
        break;
    }
    std::ofstream outfile;
    outfile.open(ErrorLog, std::ofstream::out | std::ofstream::app);
    outfile << ErrorText << "\n";
    outfile.close();
}



Logger::Logger(const std::string& local_name) : local_name(local_name){
    
}

void Logger::Log(const std::string& msg){
    char type[] = "LOG";
    this->WriteLogMessage(type,msg.data());
}

void Logger::LogWarning(const std::string& msg){
    char type[] = "WARNING";
    this->WriteLogMessage(type,msg.data());
}

void Logger::LogError(const std::string& msg){
    char type[] = "ERROR";
    this->WriteLogMessage(type,msg.data());
}

void Logger::WriteLogMessage(const char* type,const char* msg){
    time_t raw_time;
    tm* time_info;
    time(&raw_time);
    time_info = localtime(&raw_time); 
    FILE* fp = fopen("GameLog.log", "a");
    char str[500];
    int size = sprintf(str,"%s::%d/%d/%d-%d:%2d:%d@%s->%s\n",type,time_info->tm_mday,time_info->tm_mon+1,time_info->tm_year+1900,time_info->tm_hour,time_info->tm_min,time_info->tm_sec,this->local_name.data(),msg);
    fwrite(str,sizeof(char),size,fp);
    fclose(fp);
}