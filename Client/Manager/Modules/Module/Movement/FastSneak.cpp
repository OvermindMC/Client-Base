#include "FastSneak.h"

FastSneak::FastSneak(Category* c) : Module(c) {
    this->setIsEnabled(true);

    this->registerEvent<EventBase::Type::onLevel, EventBase::Priority::Low>(
        [&]() {
            Player* player = MC::getPlayer();

            if(!player)
                return;
            
            auto& ctx = player->ctx;
            auto& registry = ctx.enttRegistry;

            if(auto* sc = registry.try_get<SneakingComponent>(ctx.entity)) {
                if(auto* msc = registry.try_get<MovementSpeedComponent>(ctx.entity)) {
                    sc->mSneakSpeed = msc->mSpeed * 10.f;
                };
            };
        }
    );
};

std::string FastSneak::getName() const {
    return "Fast Sneak";
};