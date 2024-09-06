#pragma once

#include "Parent.h"

class AirJump : public Module {
public:
    AirJump(Category*);

    std::string getName() const override;
};