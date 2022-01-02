#pragma once
#include "GMpch.hpp"

class Logger{
    public:
        Logger(const std::string& local_name);
        void LogDebug(const std::string&  msg);
        void LogWarning(const std::string& msg);
        void LogError(const std::string& msg);

        static void WriteSeparator();

    private:
        void WriteLogMessage(const char* type,const char* msg);
        std::string local_name;
};