#pragma once

#include <functional>
#include <MinHook.h>
#include <Windows.h>
#include <assert.h>
#include <vector>
#include <memory>
#include <string>
#include <map>

#define PI 3.14159265358979323846

class Mem {
public:
    static HMODULE getDll();
};