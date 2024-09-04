#pragma once

#include "Parent.h"

class Flight : public Module {
public:
    Flight(Category*);

    std::string getName() const override;

    float flySpeed = 0.08f;
};