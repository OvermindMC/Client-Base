#pragma once

#include "Parent.h"

class FastSneak : public Module {
public:
    FastSneak(Category* c);
    std::string getName() const override;
};