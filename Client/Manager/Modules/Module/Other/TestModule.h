#pragma once

#include "../Module.h"

class TestMod : public Module {
public:
    TestMod(Category* c);
    std::string getName() const override;
};