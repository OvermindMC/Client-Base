#pragma once

#include "Parent.h"

class ClickGui : public Module {
public:
    ClickGui(Category*);
    ~ClickGui() override;

    std::string getName() const override;
    void revert();

    std::pair<float, float> blurProg = { 0.f, 0.f };
};