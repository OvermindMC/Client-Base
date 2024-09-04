#pragma once

#include "Parent.h"

class Flight : public Module {
public:
    Flight(Category*);
    ~Flight() override;

    std::string getName() const override;

    void revert();

    float flySpeed = 0.08f;
    bool canModify = false;
    std::pair<bool, bool> prevStates = { false, false };
};