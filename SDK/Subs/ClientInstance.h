#pragma once

#include "Entity/Player.h"
#include "GuiData/GuiData.h"

class ClientInstance {
public:
    Player* getPlayer();

    GuiData* getGuiData();
    std::string& getTopScreenName();

    BUILD_ACCESS(Vec2<float>, mousePos, 0x498);
};