#include "ClientInstance.h"

Player* ClientInstance::getPlayer() {
    return Mem::CallVFunc<Player*>(this, 29);
};

GuiData* ClientInstance::getGuiData() {
    return *(GuiData**)((uintptr_t)(this) + 0x558);
};

void ClientInstance::releaseMouse() {
    return Mem::CallVFunc<void>(this, 334);
};

void ClientInstance::grabMouse() {
    return Mem::CallVFunc<void>(this, 333);
};

std::string& ClientInstance::getTopScreenName() {
    static std::string out;
    Mem::CallVFunc<void, std::string*>(this, 147, &out);

    return out;
};