#pragma once

#include "../Sig.h"

class KeyInput_Sig : public Sig<void*> {
public:
    KeyInput_Sig() : Sig<void*>("KeyInput_Func", "48 83 EC 48 0F B6 C1 4C 8D 05", BaseSig::Type::Function) {
        //
    };
};