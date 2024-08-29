#pragma once

#include "Parent.h"

class FastSneak : public Module {
public:
    FastSneak(Category*);
    std::string getName() const override;
};