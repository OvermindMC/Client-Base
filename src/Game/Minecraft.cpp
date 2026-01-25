#include "Minecraft.h"

#include "../Mem/Mem.h"

ClientInstance* MC::getClientInstance() {
    constexpr auto sig = hat::compile_signature<"48 8B 15 ? ? ? ? 48 89 5C 24 ? C6 44 24">();
    static hat::scan_result result = hat::find_pattern(sig, ".text");

    if(uintptr_t base = result.has_result() ? (uintptr_t)result.get() : 0) {
        int off = *(int*)(base + 3);
        uintptr_t baseOff = (uintptr_t)(base + off + 7);

        if(ClientInstance* ci = (ClientInstance*)Mem::GetMultiPtr(baseOff, { 0x148, 0x40, 0x0 })) {
            return ci;
        };
    };

    return nullptr;
};