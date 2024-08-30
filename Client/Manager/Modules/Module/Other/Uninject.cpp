#include "Uninject.h"

Uninject::Uninject(Category* c) : Module(c) {
    this->setBind('U');

    this->registerEvent<EventBase::Type::onEnable, EventBase::Priority::High>(
        [&]() {
            this->getMgr()->stop();
        }
    );
};

std::string Uninject::getName() const {
    return "Uninject";
};