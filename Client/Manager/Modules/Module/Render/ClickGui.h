#pragma once

#include "Parent.h"

class ClickGui : public Module {
public:
    ClickGui(Category*);

    std::string getName() const override;

    std::pair<float, float> blurProg = { 0.f, .2f };
};