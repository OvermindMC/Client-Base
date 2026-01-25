#pragma once

#include "Entity/Context/EntityContext.h"

class Timer {
public:
    float mTicksPerSec;
    int mTicks;
    float mAlpha;
};

class Level;
class Actor;

class Minecraft {
public:
    BUILD_ACCESS(Timer, mSimTimer, 0xD0);
    BUILD_ACCESS(Timer, mRealTimer, 0xD8);

    EntityContext* getEntContext() {
        if(uintptr_t base = *(uintptr_t*)((this) + 0xB8)) {
            return (EntityContext*)(uintptr_t)((base) + 0x10);
        };
        return (EntityContext*)nullptr;
    };

    Level* getLevel();
    std::vector<Actor*> getEntities();
};