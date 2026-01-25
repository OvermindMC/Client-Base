#pragma once

#include "../../Mem/Vecs/Vec3.h"
#include "../../Mem/Macros/Access.h"

class LevelRendererPlayer {
public:
    BUILD_ACCESS(Vec3<float>, cameraPos, 0x6A4);
};

class LevelRenderer {
public:
    BUILD_PTR_ACCESS(LevelRendererPlayer, rndrPlayer, 0x3F8);
};
