#pragma once

#include "Parent.h"

class ClickGui : public Module {
public:
    ClickGui(Category*);
    ~ClickGui() override;

    std::string getName() const override;
    void revert();

    float deltaMultiplier;
    float animSpeed = 0.04f;
    std::pair<float, float> blurProg = { 0.f, 0.f };

    Vec2<float> dragStart;
};