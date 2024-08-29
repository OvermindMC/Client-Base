#include "Minecraft.h"

ClientInstance* MC::getClientInstance() {
    static uintptr_t ref = (uintptr_t)Mem::getRef("E8 ? ? ? ? 90 0F 57 C0 0F 11 45 68 66 0F 6F 0D ? ? ? ?", 0x2C);
    
    static int relOff = *(int*)(ref + 3);
    static uintptr_t baseOffset = (uintptr_t)(uintptr_t**)(ref + relOff + 7);

    static auto ptr = Mem::resPtr(baseOffset, { 0x0, 0x58, 0x0, 0x0 });
    return ptr ? (ClientInstance*)ptr : nullptr;
};

Player* MC::getPlayer() {
    ClientInstance* ci = MC::getClientInstance();
    return ci ? ci->getPlayer() : nullptr;
};