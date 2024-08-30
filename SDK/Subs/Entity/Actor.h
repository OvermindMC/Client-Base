#pragma once

#include "Context/EntityContext.h"
#include "GameMode/GameMode.h"

class Actor {
private:
    virtual ~Actor();
public:
    EntityContext ctx;

    uint64_t getRuntimeId();
    uint8_t getEntityTypeId();
    
    bool isAlive();
    bool isMoving();
    bool isJumping();

    Vec2<float> getBodyRot();

    Vec3<float> getPosition();
    void setPosition(const Vec3<float>&);

};