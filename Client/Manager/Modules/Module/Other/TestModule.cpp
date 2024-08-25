#include "TestModule.h"

void TestMod::onTick() {
    static int c = 0;

    if(c > 200) {
        Debugger::log("Goodbye");
        Sleep(2000);
        
        this->setIsEnabled(false);
        this->getMgr()->stop();
    } else {
        if(c % 2 == 0) {
            //Debugger::log(std::to_string(c));
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

void TestMod::onImRender() {
    Renderer::RenderText(
        ImVec2(
            10.f, 10.f
        ), "Hello, World!", 20.f, ImColor(255.f, 255.f, 255.f, 1.f)
    );
};

void TestMod::onLevel(void* level_ptr) {
    Debugger::log("onLevel");
};