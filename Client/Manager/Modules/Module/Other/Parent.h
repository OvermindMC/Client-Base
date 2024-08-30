#pragma once

#include "../Module.h"

#include "TestModule.h"
#include "Uninject.h"

class Other : public Category {
public:
    Other(Manager* mgr) : Category(mgr) {};

    std::string getName() const override {
        return "Other";
    };
};