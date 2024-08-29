#include "NoSlow.h"

NoSlow::NoSlow(Category* c) : Module(c) {
    this->registerEvent<EventBase::Type::onLevel, EventBase::Priority::Medium>(
        [&]() {
            Player* player = MC::getPlayer();

            if(player)
                player->ctx.removeComponent<ItemInUseComponent, BlockMovementSlowdownMultiplierComponent>();
        }
    );

    this->registerEvent<EventBase::Type::onDisable, EventBase::Priority::Low>(
        [&]() {
            this->revertPatches();
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