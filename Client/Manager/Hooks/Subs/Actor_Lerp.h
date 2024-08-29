#pragma once

#include "../Hook.h"
#include "../../Sigs/Subs/Actor_Sig.h"
#include "../../Modules/Module/Module.h"

class ActorLerp_Hook : public Hook<void, Actor*, Vec3<float>*> {
public:
    ActorLerp_Hook(Manager* mgr) : Hook<void, Actor*, Vec3<float>*>(mgr, "Actor_Lerp", mgr->getSig<Actor_Sig, void**>()[22],
    [&](Actor* entity, Vec3<float>* mMoveDelta) -> void {
        Manager* mgr = this->getMgr();
        bool cancel = false;

        if(mgr && mgr->isTicking()) {
            mgr->dispatchEvent<EventBase::Type::onLerp, Actor*, Vec3<float>*, bool&>(
                entity, mMoveDelta, cancel,
                [&](Module* m) {
                    return m->isEnabled() == true;
                }
            );
        };

        if(!cancel)
            return this->func(entity, mMoveDelta);
    }) {}
};