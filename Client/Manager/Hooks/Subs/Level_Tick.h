#pragma once

#include "../Hook.h"
#include "../../Sigs/Subs/Level_Sig.h"
#include "../../Modules/Module/Module.h"

class LevelTick_Hook : public Hook<void, void*> {
public:
    LevelTick_Hook(Manager* mgr) : Hook<void, void*>(mgr, "Level_Tick", mgr->getSig<Level_Sig, void**>()[99],
    [&](void* level) -> void {
        Manager* mgr = this->getMgr();

        if(mgr && mgr->isTicking()) {
            mgr->dispatchEvent<EventBase::Type::onLevel>(
                [&](Module* m) {
                    return m->isEnabled() || m->needsEvents();
                }
            );
        };

        return this->func(level);
    }) {}
};