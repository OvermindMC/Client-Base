#pragma once

#include "Parent.h"

class Hitbox : public Module {
public:
    Hitbox(Category*);
    ~Hitbox() override;

    std::string getName() const override;

    void revert();

    Vec2<float> tSize = Vec2<float>(2.f, 2.f);
    std::map<uint8_t, Vec2<float>> cached;
};