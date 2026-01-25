#include "ClientInstance.h"

Actor* ClientInstance::getLocalPlayer() {
    return Mem::CallVFunc<Actor*>(this, 31);
};


Level* ClientInstance::getLevel() {
    return Mem::CallVFunc<Level*>(this, 170);
};

bool ClientInstance::hasLevel() {
    return Mem::CallVFunc<bool>(this, 172);
};


LevelRenderer* ClientInstance::getLevelRenderer() {
    return Mem::CallVFunc<LevelRenderer*>(this, 188);
};

MinecraftGame* ClientInstance::getMinecraftGame() {
    return Mem::CallVFunc<MinecraftGame*>(this, 81);
};

Minecraft* ClientInstance::getMinecraft() {
    return nullptr;
};


std::string& ClientInstance::getTopScreen() {
    static std::string out;
    Mem::CallVFunc<void, std::string*>(this, 138, &out);
    return out;
};


void ClientInstance::updateChunkRadius() {
    Mem::CallVFunc<void>(this, 198);
};


void ClientInstance::grabMouse() {
    Mem::CallVFunc<void>(this, 311);
};

void ClientInstance::releaseMouse() {
    Mem::CallVFunc<void>(this, 312);
};

void ClientInstance::refocusMouse(bool lostMouse) {
    Mem::CallVFunc<void, bool>(this, 313, lostMouse);
};

void ClientInstance::setMouseType(MousePointerType type) {
    Mem::CallVFunc<void, MousePointerType>(this, 314, type);
};