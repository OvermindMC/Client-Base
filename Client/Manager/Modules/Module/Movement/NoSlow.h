#pragma once

#include "Parent.h"

class NoSlow : public Module {
public:
    NoSlow(Category*);
    std::string getName() const override;

    void revertPatches();
    ~NoSlow();
};