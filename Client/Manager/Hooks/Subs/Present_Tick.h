#pragma once

#include "../Hook.h"
#include "../../Modules/Module/Module.h"

class PresentTick_Hook : public Hook<HRESULT*, IDXGISwapChain3*, UINT, UINT> {
public:
    PresentTick_Hook(Manager* mgr) : Hook<HRESULT*, IDXGISwapChain3*, UINT, UINT>(mgr, "Present_Tick", (void*)SwapChainStub::get(8),
    [&](IDXGISwapChain3* SS, UINT SI, UINT F) -> HRESULT* {
        Manager* mgr = this->getMgr();

        if(mgr && mgr->isTicking()) {
            bool cleanAll = !Renderer::Init(SS);
            if(!cleanAll) {
                Renderer::NewFrame();

                auto& io = ImGui::GetIO();
                mgr->dispatchEvent<RenderEvent>({
                    io, io.Framerate / 60.f
                }, [&](Module* m) {
                        return m->isEnabled() || m->needsEvents();
                    }
                );
                
                Renderer::EndFrame();
            };

            Renderer::CleanUp(cleanAll);
        };

        return this->func(SS, SI, F);
    }) {}
};