#include "Step.h"

Step::Step(Category* c) : Module(c) {
    this->registerEvent<EventBase::Type::onLevel, EventBase::Priority::High>(
        [&]() {
            Player* player = MC::getPlayer();

            if(player) {
                if(auto* masc = player->ctx.tryGetComponent<MaxAutoStepComponent>()) {
                    masc->stepHeight = 2.f;
                };
            };
        }
    );

    this->registerEvent<EventBase::Type::onDisable, EventBase::Priority::High>(
        [&]() {
            Player* player = MC::getPlayer();

            if(player) {
                if(auto* masc = player->ctx.tryGetComponent<MaxAutoStepComponent>()) {
                    masc->stepHeight = 0.5625f;
                };
            };
        }
    );
};

std::string Step::getName() const {
    return "Step";
};