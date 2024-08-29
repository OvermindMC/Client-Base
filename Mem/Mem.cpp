#include "Mem.h"

HMODULE Mem::getDll() {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), reinterpret_cast<void*>(getDll), &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? static_cast<HMODULE>(info.AllocationBase) : NULL;
};

void* Mem::resPtr(uintptr_t baseOffset, const std::vector<unsigned int>& offsets, bool useGameBase) {
    uintptr_t current = baseOffset;

    if (useGameBase) {
        const auto moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
        current += moduleBase;
    };

    for (const auto& offset : offsets) {
        if (current == 0) {
            return nullptr;
        };

        current = *reinterpret_cast<uintptr_t*>(current);
        current += offset;
    };

    return reinterpret_cast<void*>(current);
};

void* Mem::getSig(std::string_view search, std::string mod) {
    hat::signature parsed = hat::parse_signature(search).value();
    hat::signature_view sig_view = hat::signature_view(parsed);
    
    hat::scan_result result = hat::find_pattern(sig_view, mod.length() > 0 ? hat::process::get_module(mod) : hat::process::get_process_module());
    return result.has_result() ? (void*)result.get() : nullptr;
};

void* Mem::getRef(std::string_view search, int offset, std::string mod) {
    uintptr_t addr = reinterpret_cast<uintptr_t>(Mem::getSig(search, mod));
    
    if (*reinterpret_cast<uint8_t*>(addr) != 0xE8) {
        return nullptr;
    };

    int32_t relOff = *reinterpret_cast<int32_t*>(addr + 1);
    return reinterpret_cast<void*>(addr + relOff + 5 + offset);
};