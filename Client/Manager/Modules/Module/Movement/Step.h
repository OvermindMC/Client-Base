#pragma once

#include "Parent.h"

class Step : public Module {
public:
    Step(Category*);

    std::string getName() const override;
};