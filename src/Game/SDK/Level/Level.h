#pragma once

#include "../../../Mem/Mem.h"

class Actor;

class Level {
private:
    virtual ~Level();
public:
    Actor* getEntity(uint64_t, bool = false);
};