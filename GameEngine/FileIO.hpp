#pragma once
#include "GMpch.hpp"
#include "Debug.hpp"
#include "json/json.hpp"


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
    //Tries to get value, if it fails then debug error
    template<typename T>
        bool TryToRead(nlohmann::json j,const std::string& e,T* value = nullptr){
            if(j.contains(e)){
                try{
                    *value = j[e].get<T>();
                    return true;
                }catch(nlohmann::json::type_error){
                    // !! DEBUG ERROR !!
                    std::cout << " !! TYPE ERROR !!\n";
                    return false;
                }
            }else{
                if(strcmp(e.data(),"__THIS_CELL__") == 0){
                    try{
                        *value = j.get<T>();
                    }catch(nlohmann::json::type_error){
                        // !! DEBUG ERROR !!
                        std::cout << " !! TYPE ERROR !!\n";
                        return false; 
                    }
                }
            }
            return false;
    };
}