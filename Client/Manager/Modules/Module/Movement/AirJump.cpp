#include "AirJump.h"

struct OnGroundFlagComponent : public EntityComponent {
    OnGroundFlagComponent() {};
};

AirJump::AirJump(Category* c) : Module(c) {
    this->registerEvent<LevelEvent, EventPriority::Medium>(
        [&](const LevelEvent& ev) {
            if(!ev.mPlayer)
                return;
            
            Player* player = ev.mPlayer;
            if(!player->ctx.hasComponent<OnGroundFlagComponent>()) {
                player->ctx.addComponent<OnGroundFlagComponent>();
            };
        }
    );
};

std::string AirJump::getName() const {
    return "AirJump";
};