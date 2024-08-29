#include "ClientInstance.h"

Player* ClientInstance::getPlayer() {
    return Mem::CallVFunc<Player*>(this, 29);
};