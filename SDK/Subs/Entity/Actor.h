#pragma once

#include "Context/EntityContext.h"

class Actor {
private:
    virtual ~Actor();
public:
    EntityContext ctx;
};