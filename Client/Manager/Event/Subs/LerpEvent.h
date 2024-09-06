#pragma once

#include "Cancellable.h"

class Actor;

struct ActorLerpEvent : public CancellableEvent {
    Actor* mActor;
    Vec3<float>& mLerp;
};