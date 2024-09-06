#pragma once

#include "Cancellable.h"

struct KeyInputEvent : public CancellableEvent {
    uint64_t mKey;
    bool mIsDown;
};