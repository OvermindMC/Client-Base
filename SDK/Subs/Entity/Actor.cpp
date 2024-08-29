#include "Actor.h"

bool Actor::isMoving() {
    if(auto* svc = this->ctx.tryGetComponent<StateVectorComponent>()) {
        return svc->mMotion.magnitudeXZ() >= 0.1f;
    };
    return false;
};