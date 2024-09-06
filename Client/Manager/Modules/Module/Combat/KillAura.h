#pragma once

#include "Parent.h"

class Killaura : public Module {
public:
    Killaura(Category*);

    std::string getName() const override;

    float range = 12.f;
    float ticksDelay = 0.5f;
};