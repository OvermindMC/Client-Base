#pragma once

#include "../../../../Mem/Mem.h"
#include "../../../../Utils/Utils.h"

struct CancellableEvent {
    bool& cancel;
};