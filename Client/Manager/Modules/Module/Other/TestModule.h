#pragma once

#include "../Module.h"

class TestMod : public Module {
public:
    TestMod(Category*);
    std::string getName() const override;
};