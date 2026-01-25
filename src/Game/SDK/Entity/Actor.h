#pragma once

#include "Context/EntityContext.h"

#include "Context/Components/RuntimeID.h"
#include "Context/Components/MaxAutoStep.h"
#include "Context/Components/ActorUniqueID.h"
#include "Context/Components/LevelComponent.h"
#include "Context/Components/ActorOwnerComponent.h"

#include "../Level/Level.h"

class Actor {
private:
    virtual ~Actor();
public:
    EntityContext ctx;

    BUILD_PTR_ACCESS(Level, level, 0x1D8);
};