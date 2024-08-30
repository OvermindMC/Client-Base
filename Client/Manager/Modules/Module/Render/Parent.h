#pragma once

#include "../Module.h"

#include "ClickGui.h"

class Render : public Category {
public:
    Render(Manager* mgr) : Category(mgr) {};

    std::string getName() const override {
        return "Render";
    };
};