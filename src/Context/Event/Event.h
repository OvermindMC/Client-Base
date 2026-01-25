#pragma once

class MinecraftUIRenderCtx;

namespace Events {
    struct OnTick {
        //
    };

    struct OnUIRenderCtx {
        MinecraftUIRenderCtx* ctx;
    };
};