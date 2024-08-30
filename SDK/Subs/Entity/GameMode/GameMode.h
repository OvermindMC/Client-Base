#pragma once

#include "../../../../Mem/Mem.h"

class Actor;
class Player;

class GameMode {
private:
    virtual ~GameMode();
public:
    virtual bool startDestroyBlock(Vec3<int>* pos, unsigned __int8 face, bool hasDestroyedBlock);
    virtual bool destroyBlock(Vec3<int>* pos, unsigned __int8 face);
    virtual bool continueDestroyBlock(Vec3<int>* pos, unsigned __int8 face, Vec3<float> const& playerPos, bool hasDestroyedBlock);
    virtual void stopDestroyBlock(Vec3<int>* pos);
    virtual void startBuildBlock(Vec3<int>* pos, unsigned __int8 face);
    virtual bool buildBlock(Vec3<int>* pos, unsigned __int8 face, bool);
    virtual void continueBuildBlock(Vec3<int>* pos, unsigned __int8 face);
    virtual void stopBuildBlock();
    virtual void tick();
    virtual float getPickRange(enum InputMode* currentInputMode, bool isVR);
    virtual bool useItem(class ItemStack*);
    virtual class InteractionResult useItemOn(
        class ItemStack&      item,
        Vec3<int>*            at,
        unsigned __int8       face,
        Vec3<int>*            hit,
        class Block const*    targetBlock
    );
    virtual bool interact(Actor* entity, Vec3<int>* location);
    virtual bool attack(Actor* entity);
    virtual void releaseUsingItem();
    virtual void setTrialMode(bool isEnabled);
    virtual bool isInTrialMode();
public:
    Player* player;
};