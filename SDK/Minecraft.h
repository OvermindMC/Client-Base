#pragma once

#include "Subs/ClientInstance.h"

class MC {
public:
    static ClientInstance* getClientInstance();
    static Player* getPlayer();
};