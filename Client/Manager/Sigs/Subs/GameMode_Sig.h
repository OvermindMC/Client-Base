#pragma once

#include "../Sig.h"

class GameMode_Sig : public Sig<void**> {
public:
    GameMode_Sig() : Sig<void**>("GameMode_VTable", "48 8D 05 ? ? ? ? 48 8B D9 48 89 01 48 8B 89 ? ? ? ? 48 85 C9 74 11 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 48 8B 8B ? ? ? ? 48 85 C9 74 17", BaseSig::Type::VTable) {
        //
    };
};