#include "Player.h"

GameMode* Player::getGameMode() {
    return *(GameMode**)((uintptr_t)(this) + 0xB00);
};

std::string Player::getUsername() {
    return ((std::string*)((uintptr_t)(this) + 0xC88))->c_str();
};

void Player::swing() {
    return Mem::CallVFunc<void>(this, 115);
};

void Player::setSprinting(bool state) {
    return Mem::CallVFunc<void, bool>(this, 150, state);
};

void Player::displayClientMsg(std::string messageContents) {
    return Mem::CallVFunc<void, std::string*, std::string*>(this, 210, &messageContents, &messageContents);
};