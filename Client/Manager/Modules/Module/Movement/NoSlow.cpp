#include "NoSlow.h"

NoSlow::NoSlow(Category* c) : Module(c) {
    this->registerEvent<LevelEvent, EventPriority::Medium>(
        [&](const LevelEvent& ev) {
            if(ev.mPlayer) {
                ev.mPlayer->ctx.removeComponent<ItemInUseComponent, BlockMovementSlowdownMultiplierComponent>();
            };
        }
    );

    this->registerEvent<ModuleEvent, EventPriority::Low>(
        [&](const ModuleEvent& ev) {
            if(!ev.isEnabled) {
                this->revertPatches();
            };
        }
    );
};

std::string NoSlow::getName() const {
    return "NoSlow";
};

void NoSlow::revertPatches() {
    Player* player = MC::getPlayer();

    if(player)
        player->ctx.addComponent<BlockMovementSlowdownMultiplierComponent>();
};

NoSlow::~NoSlow() {
    revertPatches();
};