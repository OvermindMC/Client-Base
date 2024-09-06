#pragma once

#include "Cancellable.h"

enum class MouseAction : char {
    LMOUSE = 1, RMOUSE = 2, WHEELCLICK = 3, WHEELSCROLL = 4
};

struct MouseInputEvent : public CancellableEvent {
    MouseAction mAction;
    bool mIsDown;
    Vec2<int> mMousePos;
};