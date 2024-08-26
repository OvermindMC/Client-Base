#include "TestModule.h"

void TestMod::onTick() {
    //
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