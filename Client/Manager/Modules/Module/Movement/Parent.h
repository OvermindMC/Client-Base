#pragma once

#include "../Module.h"

#include "FastSneak.h"

class Move : public Category {
public:
    Move(Manager* mgr) : Category(mgr) {};

    std::string getName() const override {
        return "Movement";
    };
};