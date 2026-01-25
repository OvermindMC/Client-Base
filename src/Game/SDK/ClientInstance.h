#pragma once

#include "LevelRenderer.h"
#include "Entity/Actor.h"
#include "Level/Level.h"

#include "MinecraftGame.h"
#include "Minecraft.h"

enum class MousePointerType : int {
    Arrow = 0, Hand = 1
};

class ClientInstance {
public:
    Actor* getLocalPlayer();
    
    Level* getLevel();
    bool hasLevel();

    LevelRenderer* getLevelRenderer();
    MinecraftGame* getMinecraftGame();
    Minecraft* getMinecraft();

    std::string& getTopScreen();

    void updateChunkRadius();

    void grabMouse();
    void releaseMouse();
    void refocusMouse(bool = false);
    void setMouseType(MousePointerType);
public:
    BUILD_PTR_ACCESS(LevelRenderer, lvlRendr, 0x1B8);
    BUILD_PTR_ACCESS(MinecraftGame, mcGame, 0x1A0);
    BUILD_PTR_ACCESS(Minecraft, mc, 0x1A8);
};