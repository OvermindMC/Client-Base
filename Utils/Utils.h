#pragma once

#include "Render/OverFX/OverFX.h"
#include "Debugger/Debugger.h"
#include "Render/Renderer.h"

class Utils {
public:
    static void reachOffset(float* offset, float target, float modifier);
    static std::string sanitize(std::string&);
};