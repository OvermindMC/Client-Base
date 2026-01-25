#include "Level.h"

Actor* Level::getEntity(uint64_t runtimeId, bool wasRemoved) {
    return Mem::CallVFunc<Actor*, uint64_t, bool>(this, 59, runtimeId, wasRemoved);
};