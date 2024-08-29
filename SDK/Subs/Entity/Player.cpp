#include "Player.h"

void Player::setSprinting(bool state) {
    return Mem::CallVFunc<void, bool>(this, 150, state);
};