#pragma once

#include "../Module.h"

#include "AutoSprint.h"
#include "FastSneak.h"
#include "NoSlow.h"

class Move : public Category {
public:
    Move(Manager* mgr) : Category(mgr) {};

    std::string getName() const override {
        return "Movement";
    };
};