#pragma once

#include "../Module.h"

class TestMod : public Module {
public:
    TestMod(Category* c) : Module(c) {
        this->setIsEnabled(true);
    };

    std::string getName() const override {
        return "Test Module";
    };

    void onTick() override;
    void onEnable() override;
    void onDisable() override;
    void onLevel(void*) override;
};