#pragma once

#include "Subs/ClientInstance.h"

class MC {
public:
    static ClientInstance* getClientInstance();
    static Player* getPlayer();

    static std::vector<Actor*> getEntities();
};

class MCUtils {
public:
    static bool isHostile(uint8_t);
    static bool isPassive(uint8_t);

    static void forEach(std::function<void(Actor*, bool&)> callback, std::function<bool(Actor*, Actor*)> sort = nullptr, std::function<bool(Actor*)> includeOnly = nullptr);
};