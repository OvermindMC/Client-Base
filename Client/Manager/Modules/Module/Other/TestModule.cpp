#include "TestModule.h"

TestMod::TestMod(Category* c) : Module(c) {
    this->setIsEnabled(true);

    this->registerEvent<EventBase::Type::onTick, EventBase::Priority::High>(
        [&]() {
            //Debugger::log("OnTick");
        }
    );

    this->registerEvent<EventBase::Type::onEnable, EventBase::Priority::High>(
        [&]() {
            //Debugger::log("OnEnable");
        }
    );

    this->registerEvent<EventBase::Type::onDisable, EventBase::Priority::High>(
        [&]() {
            //Debugger::log("OnDisable");
        }
    );

    this->registerEvent<EventBase::Type::onLevel, EventBase::Priority::High>(
        [&]() {
            //Debugger::log("OnLevel");
        }
    );

    this->registerEvent<EventBase::Type::onRender, EventBase::Priority::High>(
        [&]() {
            //Debugger::log("OnRender");
        }
    );
};

std::string TestMod::getName() const {
    return "Test Module";
};