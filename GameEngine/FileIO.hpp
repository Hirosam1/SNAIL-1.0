#pragma once
#include "GMpch.hpp"
#include "Debug.hpp"


namespace FileIO{
    //inline to ensure function definition
    inline std::string ReadFromFile(std::string& file_path){
            std::ifstream in(file_path);
            if(!in){
                std::cout<<"File " <<file_path<<" was NOT successfully opened!!\n";
                Debug::WriteErrorLog("ERROR::FileIO","File "+file_path+" was not successfully opened!");
            }
            std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            return contents;
    }
}