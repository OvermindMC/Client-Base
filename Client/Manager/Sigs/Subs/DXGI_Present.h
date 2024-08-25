#pragma once

#include "../Sig.h"

class DXGIPresent_Sig : public Sig<void**> {
public:
    DXGIPresent_Sig() : Sig<void**>("DXGIPresent_Func", "48 89 5C 24 10 48 89 74 24 20 55 57 41 56", BaseSig::Type::Function, "dxgi.dll") {
        //
    };
};