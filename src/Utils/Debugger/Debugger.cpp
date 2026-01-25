#include "Debugger.h"

bool Debugger::mInits = false;

void Debugger::Init() {
    if(Debugger::mInits)
        return;
    
    if(AllocConsole()) {
        FILE* cFile;

        if(freopen_s(&cFile, "CONOUT$", "w", stdout) > 0) {
            FreeConsole();
        } else {
            Debugger::mInits = true;
            Log("Debugger Initialized!");
        };
    };
};

void Debugger::Destroy() {
    if(!Debugger::mInits)
        return;
    
    fclose(stdout);
    FreeConsole();
};

void Debugger::Log(std::string out) {
    if(!Debugger::mInits)
        return;
    
    printf("[%s] %s\n", GetTime().c_str(), out.c_str());
    fflush(stdout);
};

std::string Debugger::GetTime() {
    std::time_t now = std::time(nullptr);
    
    std::tm tm{};
    localtime_s(&tm, &now);

    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);

    return buf;
};