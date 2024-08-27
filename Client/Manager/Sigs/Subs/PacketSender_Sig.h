#pragma once

#include "../Sig.h"

class PacketSender_Sig : public Sig<void**> {
public:
    PacketSender_Sig() : Sig<void**>("PacketSender_VTable", "48 8D 05 ? ? ? ? 48 8B 5C 24 ? 48 89 06 33 C0 48 89 7E ? C6 46 ? 01 48", BaseSig::Type::VTable) {
        //
    };
};