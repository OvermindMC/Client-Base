#pragma once

#include "../Module.h"

#include "AutoSprint.h"
#include "FastSneak.h"
#include "Velocity.h"
#include "Flight.h"
#include "NoSlow.h"
#include "Step.h"

class Move : public Category {
public:
    Move(Manager* mgr) : Category(mgr) {};

    std::string getName() const override {
        return "Movement";
    };
};