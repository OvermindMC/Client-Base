#pragma once

#include "../Module.h"

#include "KillAura.h"

class Combat : public Category {
public:
    Combat(Manager* mgr) : Category(mgr) {};

    std::string getName() const override {
        return "Combat";
    };
};