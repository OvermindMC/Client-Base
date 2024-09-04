#pragma once

#include "../Module.h"

#include "KillAura.h"
#include "Hitbox.h"

class Combat : public Category {
public:
    Combat(Manager* mgr) : Category(mgr) {};

    std::string getName() const override {
        return "Combat";
    };
};