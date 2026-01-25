#pragma once

#include "../Hook.h"
#include "../../ClientContext.h"

template<>
struct HookTraits<class UIRenderCtxHook> {
    static constexpr std::string_view Name = "UIRenderCtx";
    static void* GetTarget() {
        static auto sig = Mem::GetSig("48 89 5C 24 18 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 BC 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B");
        return sig;
    };
};

class UIRenderCtxHook final : public Hook<void, void*, MinecraftUIRenderCtx*> {
    public:
    explicit UIRenderCtxHook(ClientContext* ctx) : Hook<void, void*, MinecraftUIRenderCtx*>(
        ctx, HookTraits<UIRenderCtxHook>::Name, HookTraits<UIRenderCtxHook>::GetTarget(), [](Hook& hook, void* a1, MinecraftUIRenderCtx* ctx) -> void {
            if(ClientContext* clientCtx = hook.getContext()) {
                if(!clientCtx->IsShuttingDown()) {
                    clientCtx->getEvents().Dispatch<Events::OnUIRenderCtx>({ ctx });
                    hook.CallOriginal(a1, ctx);
                };
            };
        }
    ){}
};