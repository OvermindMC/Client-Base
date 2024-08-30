#pragma once

#include "../Sig.h"

class MouseInput_Sig : public Sig<void*> {
public:
    MouseInput_Sig() : Sig<void*>("MouseInput_Func", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 54 41 55 41 56 41 57 48 83 EC 60", BaseSig::Type::Function) {
        //
    };
};