#include "ClientInstance.h"

Player* ClientInstance::getPlayer() {
    return Mem::CallVFunc<Player*>(this, 29);
};

GuiData* ClientInstance::getGuiData() {
    return *(GuiData**)((uintptr_t)(this) + 0x558);
};

std::string& ClientInstance::getTopScreenName() {
    static std::string out;
    Mem::CallVFunc<void, std::string*>(this, 147, &out);

    return out;
};