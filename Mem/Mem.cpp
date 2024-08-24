#include "Mem.h"

HMODULE Mem::getDll() {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), reinterpret_cast<void*>(getDll), &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? static_cast<HMODULE>(info.AllocationBase) : NULL;
};