#include "Velocity.h"

Velocity::Velocity(Category* c) : Module(c) {
    this->registerEvent<EventBase::Type::onLerp, EventBase::Priority::High, Actor*, Vec3<float>*, bool&>(
        [&](Actor* entity, Vec3<float>* mMoveDelta, bool& cancel) {
            cancel = true;
        }
    );
};

std::string Velocity::getName() const {
    return "Velocity";
};