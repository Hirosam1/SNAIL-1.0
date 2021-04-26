#pragma once
#include "GMpch.hpp"
#include "Debug.hpp"


namespace FileIO{
    //inline to ensure function definition
    inline std::string ReadFromFile(std::string& file_path){
            std::ifstream in(file_path);
            if(!in){
                #ifdef DEBUG
                std::cout<<"File " <<file_path<<" was NOT successfully opened!!\n";
                #endif
                Debug::WriteErrorLog(ErrorType::FILE_LOAD_TEXT_FAIL,&file_path);
            }
            std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            return contents;
    }
}