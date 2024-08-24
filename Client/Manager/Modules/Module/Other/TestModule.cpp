#include "TestModule.h"

void TestMod::onTick() {
    static int c = 0;

    if(c > 100) {
        Debugger::log("Goodbye");
        Sleep(1000);
        
        this->setIsEnabled(false);
        this->getMgr()->stop();
    } else {
        if(c % 2 == 0) {
            Debugger::log(std::to_string(c));
        };
        c++;
    };
};

void TestMod::onEnable() {
    Debugger::log(
        this->getName() + " Enabled!"
    );
};

void TestMod::onDisable() {
    Debugger::log(
        this->getName() + " Disabled!"
    );
};

void TestMod::onLevel(void* level_ptr) {
    Debugger::log("onLevel");
};