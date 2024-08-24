#include "Debugger.h"

std::string Debugger::outname = "Debugger";
bool Debugger::doneInit = false;

void Debugger::init(std::string outName) {
    if(Debugger::doneInit)
        return;
    
    Debugger::outname = outName.c_str();
    if(AllocConsole()) {
        FILE* oFile = nullptr;
        Debugger::doneInit = freopen_s(&oFile, "CONOUT$", "w", stdout) == 0;
    };
};

void Debugger::free() {
    if(!Debugger::doneInit)
        return;
    
    fclose(stdout);
    FreeConsole();
};

void Debugger::log(std::string output) {
    if(!Debugger::doneInit)
        return;
    
    printf("<%s> %s\n", std::string(Debugger::outname + ":" + genTimeStamp()).c_str(), output.c_str());
    fflush(stdout);
};

std::string Debugger::genTimeStamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    std::string timestamp = oss.str();
    return timestamp;
};