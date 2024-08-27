#pragma once

#include "../Sig.h"

class HandleLook_Sig : public Sig<void*> {
public:
    HandleLook_Sig() : Sig<void*>("HandleLook_Func", "48 89 5C 24 ? 57 48 83 EC ? F3 41 0F 10 00 49 8B D8 F3 41 0F 58 40", BaseSig::Type::Function) {
        //
    };
};