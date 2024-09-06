#include "Actor.h"

uint64_t Actor::getRuntimeId() {
    if(auto* ric = this->ctx.tryGetComponent<RuntimeIDComponent>()) {
        return ric->mRuntimeId;
    };
    return 0;
};

uint8_t Actor::getEntityTypeId() {
    if(auto* atc = this->ctx.tryGetComponent<ActorTypeComponent>()) {
        return atc->getType();
    };
    return 0;
};

bool Actor::isAlive() {
    return Mem::CallVFunc<bool>(this, 48);
};

bool Actor::isMoving() {
    if(auto svc = this->ctx.tryGetComponent<StateVectorComponent>()) {
        return svc->mMotion.magnitudeXZ() >= 0.1f;
    };
    return false;
};

bool Actor::isJumping() {
    return this->ctx.hasComponent<MobIsJumpingFlagComponent>();
};

Vec2<float> Actor::getBodyRot() {
    if(auto arc = this->ctx.tryGetComponent<ActorRotationComponent>()) {
        return arc->mRot;
    };
    return {};
};

Vec3<float> Actor::getPosition() {
    if(auto svc = this->ctx.tryGetComponent<StateVectorComponent>()) {
        return svc->mPos;
    };
    return {};
};

void Actor::setPosition(const Vec3<float>& position) {
    if(!this->ctx.hasComponent<ActorSetPositionRequestComponent>()) {
        this->ctx.addComponent<ActorSetPositionRequestComponent>(std::move(position));
    };
};