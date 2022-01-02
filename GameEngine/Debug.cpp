#include "Debug.hpp"

Logger::Logger(const std::string& local_name) : local_name(local_name){
    
}

void Logger::LogDebug(const std::string& msg){
    char type[] = "DEBUG";
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

void Logger::WriteSeparator(){
    FILE* fp = fopen("GameLog.log", "a");
    char str[] = "\n\n==============================================\n\n";
    fwrite(str,sizeof(char),sizeof(str)/sizeof(char)-1,fp);
    fclose(fp);
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