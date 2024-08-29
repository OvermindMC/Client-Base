#pragma once

#include "../Sig.h"

class Actor_Sig : public Sig<void**> {
public:
    Actor_Sig() : Sig<void**>("Actor_VTable", "48 8D 05 ? ? ? ? 48 89 06 83 8E ? ? ? ? ?", BaseSig::Type::VTable) {
        //
    };
};