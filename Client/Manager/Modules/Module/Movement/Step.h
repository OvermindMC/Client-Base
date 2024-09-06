#pragma once

#include "Parent.h"

class Step : public Module {
public:
    Step(Category*);
    ~Step() override;

    std::string getName() const override;

    void revert();
};