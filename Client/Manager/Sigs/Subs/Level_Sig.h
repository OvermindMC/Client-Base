#pragma once

#include "../Sig.h"

class Level_Sig : public Sig<void**> {
public:
    Level_Sig() : Sig<void**>("Level_VTable", "48 8D 05 ? ? ? ? 48 89 ? 48 8D 05 ? ? ? ? 48 89 ? 18 48 8D 05 ? ? ? ? 48 89 ? 20 ? ? ? ? ? ? ? 48 ? ? ? ? E8 ? ? ? ? 48 8B", BaseSig::Type::VTable) {
        //
    };
};