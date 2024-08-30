#pragma once

#include <libhat/Scanner.hpp>
#include <functional>
#include <algorithm>
#include <MinHook.h>
#include <Windows.h>
#include <assert.h>
#include <vector>
#include <memory>
#include <string>
#include <map>

#define PI 3.14159265358979323846

#include "Macro/Macros.hpp"
#include "Math/AABB.h"
#include "Math/Vec4.h"
#include "EnTT/EnTT.h"

class Mem {
public:
    static HMODULE getDll();
    
    static void* resPtr(uintptr_t baseOffset, const std::vector<unsigned int>& offsets, bool useGameBase = false);
    static void* getSig(std::string_view search, std::string mod = "");
    static void* getRef(std::string_view search, int off = 0, std::string mod = "");

    template<typename T, typename... Args>
    static inline T CallVFunc(void* ptr, unsigned int index, Args... args) {
        using Func = T (__thiscall*)(void*, Args...);
        return (*static_cast<Func**>(ptr))[index](ptr, args...);
    };
};