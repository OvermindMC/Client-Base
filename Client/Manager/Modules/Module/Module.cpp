#include "Module.h"

Module::Module(Category* c) : cPtr(c), evH(std::make_unique<EventHandler>()) {};

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
            this->evH->dispatchEvent<EventBase::Type::onEnable>();
        } else {
            this->evH->dispatchEvent<EventBase::Type::onDisable>();
        };
    };

    if(this->state.first) {
        this->evH->dispatchEvent<EventBase::Type::onTick>();
    };
};

void Module::setIsEnabled(bool state) {
    this->state.first = state;
};

bool Module::isEnabled() const {
    return this->state.first;
};

bool Module::wasEnabled() const {
    return this->state.second;
};