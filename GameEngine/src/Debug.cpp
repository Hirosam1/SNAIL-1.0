#include "Debug.hpp"


const char ErrorLog[] = "ErrorLog.log";
void Debug::CleanErrorLog(){
    std::ofstream outfile;
    outfile.open(ErrorLog, std::ofstream::out | std::ofstream::trunc);
    outfile.close();
}

void Debug::WriteErrorLog(std::string location,std::string line){
    std::ofstream outfile;
    outfile.open(ErrorLog, std::ofstream::out | std::ofstream::app);
    outfile <<location<<"(" <<line << ")\n";
    outfile.close();
}