#pragma once

#include "Entity/Player.h"

class ClientInstance {
public:
    Player* getPlayer();

    std::string& getTopScreenName();
};