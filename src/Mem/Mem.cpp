#include "Mem.h"

HMODULE Mem::GetDll() {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), reinterpret_cast<void*>(GetDll), &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? static_cast<HMODULE>(info.AllocationBase) : NULL;
};

uintptr_t Mem::GetMultiPtr(uintptr_t base, const std::vector<unsigned int>& offsets) {
    if(!base || offsets.empty())
        return 0;

    uintptr_t addr = base;
    
    for(const auto& offset : offsets) {
        __try {
            addr = *(uintptr_t*)(addr);
            addr += offset;
        }
        __except(EXCEPTION_EXECUTE_HANDLER) {
            return 0;
        };
    };

    return addr;
};

void* Mem::GetSig(std::string_view pattern, std::string_view module) {
    hat::signature_view sig_view = hat::signature_view(
        hat::parse_signature(pattern).value()
    );

    auto mod = module.empty() ? hat::process::get_process_module() : hat::process::get_module(module);
    auto data = mod->get_module_data();
    
    hat::scan_result result = hat::find_pattern(
        data.begin(), data.end(), sig_view
    );

    return result.has_result() ? result.get() : nullptr;
};