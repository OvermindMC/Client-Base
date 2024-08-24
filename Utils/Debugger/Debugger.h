#pragma once

#include <Windows.h>
#include <sstream>
#include <string>
#include <chrono>

class Debugger {
public:
    static void init(std::string);
    static void free();

    static void log(std::string);
    static std::string genTimeStamp();
private:
    static std::string outname;
    static bool doneInit;
};