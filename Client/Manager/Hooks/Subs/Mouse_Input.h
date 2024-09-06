#pragma once

#include "../Hook.h"
#include "../../Sigs/Subs/Mouse_Input.h"
#include "../../Modules/Module/Module.h"

class MouseInput_Hook : public Hook<void, void*, char, bool, short, short, short, short, bool> {
public:
    MouseInput_Hook(Manager* mgr) : Hook<void, void*, char, bool, short, short, short, short, bool>(mgr, "Level_Tick", mgr->getSig<MouseInput_Sig, void*>(),
    [&](void* p1, char action, bool isDown, short mouseX, short mouseY, short movementX, short movementY, bool scroll) -> void {
        Manager* mgr = this->getMgr();
        bool cancel = false;

        if(mgr && mgr->isTicking()) {
            mgr->dispatchEvent<MouseInputEvent>(
                {
                    cancel, static_cast<MouseAction>(action), isDown, Vec2<int>(mouseX, mouseY)
                }, [&](Module* m) {
                    return m->isEnabled() || m->needsEvents();
                }
            );
        };

        if(!cancel)
            return this->func(p1, action, isDown, mouseX, mouseY, movementX, movementY, scroll);
    }) {}
};