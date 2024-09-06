#include "Velocity.h"

Velocity::Velocity(Category* c) : Module(c) {
    this->registerEvent<ActorLerpEvent, EventPriority::High>(
        [&](const ActorLerpEvent& ev) {
            ev.cancel = true;
        }
    );
};

std::string Velocity::getName() const {
    return "Velocity";
};