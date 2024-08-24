#include "Module.h"

Category* Module::getCategory() const {
    return this->cPtr;
};

Manager* Module::getMgr() const {
    return this->cPtr ? this->cPtr->getMgr() : nullptr;
};

void Module::baseTick() {
    if(this->state.first != this->state.second) {
        this->state.second = this->state.first;

        if(this->state.first) {
            this->onEnable();
        } else {
            this->onDisable();
        };
    };

    if(this->state.first) {
        this->onTick();
    };
};

bool Module::isEnabled() const {
    return this->state.first;
};

void Module::setIsEnabled(bool state) {
    this->state.first = state;
};