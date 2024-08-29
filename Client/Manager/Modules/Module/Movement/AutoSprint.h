#pragma once

#include "Parent.h"

class AutoSprint : public Module {
public:
    AutoSprint(Category*);
    std::string getName() const override;
};