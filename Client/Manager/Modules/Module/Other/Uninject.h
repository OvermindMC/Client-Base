#pragma once

#include "Parent.h"

class Uninject : public Module {
public:
    Uninject(Category*);

    std::string getName() const override;
};