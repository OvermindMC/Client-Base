#pragma once

#include "../../Mem/Macros/Access.h"

class ClientInstance;

class MinecraftUIRenderCtx {
public:
    BUILD_PTR_ACCESS(ClientInstance, clientInstance, 0x8);
};