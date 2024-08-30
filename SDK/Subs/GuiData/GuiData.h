#pragma once

#include "../../Mem/Mem.h"

class GuiData {
public:
    BUILD_ACCESS(float, uiScale, 0x4C);
    BUILD_ACCESS(Vec2<int>, mousePos, 0x68);
    BUILD_ACCESS(Vec2<float>, windowSize, 0x30);
    BUILD_ACCESS(Vec2<float>, windowSizeScaled, 0x40);
};