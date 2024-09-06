#include "Step.h"

Step::Step(Category* c) : Module(c) {
    this->registerEvent<LevelEvent, EventPriority::High>(
        [&](const LevelEvent& ev) {
            if(ev.mPlayer) {
                if(auto* masc = ev.mPlayer->ctx.tryGetComponent<MaxAutoStepComponent>()) {
                    masc->stepHeight = 2.f;
                };
            };
        }
    );

    this->registerEvent<ModuleEvent, EventPriority::High>(
        [&](const ModuleEvent& ev) {
            if(!ev.isEnabled) {
                Player* player = MC::getPlayer();

                if(player) {
                    if(auto* masc = player->ctx.tryGetComponent<MaxAutoStepComponent>()) {
                        masc->stepHeight = 0.5625f;
                    };
                };
            };
        }
    );
};

std::string Step::getName() const {
    return "Step";
};