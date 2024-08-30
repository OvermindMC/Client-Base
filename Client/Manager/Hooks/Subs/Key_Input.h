#pragma once

#include "../Hook.h"
#include "../../Sigs/Subs/KeyInput_Sig.h"
#include "../../Modules/Module/Module.h"

class KeyInput_Hook : public Hook<void, uint64_t, bool> {
public:
    KeyInput_Hook(Manager* mgr) : Hook<void, uint64_t, bool>(mgr, "Key_Input", mgr->getSig<KeyInput_Sig, void*>(),
    [&](uint64_t key, bool isDown) -> void {
        Manager* mgr = this->getMgr();
        bool cancel = false;

        if(mgr && mgr->isTicking()) {
            mgr->isUsingKey(key, isDown);

            mgr->dispatchEvent<EventBase::Type::onLevel, uint64_t, bool, bool&>(key, isDown, cancel,
                [&](Module* m) {
                    return m->isEnabled();
                }
            );

            ClientInstance* ci = MC::getClientInstance();

            if(isDown && ci) {
                Player* player = ci->getPlayer();
                bool isInHud = ci->getTopScreenName().rfind("hud_screen") != std::string::npos;

                if(player && isInHud || player == nullptr && !isInHud) {
                    for(const auto& category : mgr->getCategories()) {
                        for(const auto& module : category->getModules()) {
                            if(module->getBind() == key) {
                                module->toggleIsEnabled();
                            };
                        };
                    };
                };
            };
        };

        if(!cancel)
            return this->func(key, isDown);
    }) {}
};