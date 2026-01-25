#pragma once

#include <type_traits>
#include <functional>
#include <Windows.h>
#include <assert.h>
#include <cstdint>
#include <sstream>
#include <variant>
#include <vector>
#include <string>
#include <atomic>
#include <mutex>
#include <map>

#include <libhat/scanner.hpp>
#include <MinHook.h>

#include "EnTT/EnTT.h"
#include "Vecs/Vec3.h"
#include "Macros/Access.h"

class Mem {
public:
    static HMODULE GetDll();
    static uintptr_t GetMultiPtr(uintptr_t, const std::vector<unsigned int>&);
    static void* GetSig(std::string_view, std::string_view = "");

    template<typename T, typename... Args>
    static inline T CallVFunc(void* ptr, unsigned int index, Args... args) {
        using Fn = T(__fastcall*)(void*, decltype(args)...);
        return (*static_cast<Fn**>((void*)ptr))[index]((void*)ptr, args...);
    };
};