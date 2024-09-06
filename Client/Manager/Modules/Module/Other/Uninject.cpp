#include "Uninject.h"

Uninject::Uninject(Category* c) : Module(c) {
    this->setBind('U');

    this->registerEvent<ModuleEvent, EventPriority::High>(
        [&](const ModuleEvent& ev) {
            if(ev.isEnabled) {
                this->getMgr()->stop();
            };
        }
    );
};

std::string Uninject::getName() const {
    return "Uninject";
};