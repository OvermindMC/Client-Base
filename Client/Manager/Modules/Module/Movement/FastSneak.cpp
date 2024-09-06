#include "FastSneak.h"

FastSneak::FastSneak(Category* c) : Module(c) {
    this->registerEvent<LevelEvent, EventPriority::Low>(
        [&](const LevelEvent& ev) {
            if(ev.mPlayer) {
                if(auto* sc = ev.mPlayer->ctx.tryGetComponent<SneakingComponent>()) {
                    if(auto* msc = ev.mPlayer->ctx.tryGetComponent<MovementSpeedComponent>()) {
                        sc->mSneakSpeed = msc->mSpeed * 10.f;
                    };
                };
            };
        }
    );
};

std::string FastSneak::getName() const {
    return "Fast Sneak";
};