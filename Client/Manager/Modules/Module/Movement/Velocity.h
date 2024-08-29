#pragma once

#include "Parent.h"

class Velocity : public Module {
public:
    Velocity(Category*);

    std::string getName() const override;
};