#pragma once

#include <Windows.h>
#include <iostream>
#include <memory>
#include <string>
#include <ctime>

class Debugger {
public:
    static void Init();
    static void Destroy();

    static void Log(std::string);
    static std::string GetTime();
private:
    static bool mInits;
};