#pragma once

#include "../../Module.h"
#include "../ModuleTraits.h"

class TestMod final : public Module {
public:
    explicit TestMod(Category*) noexcept;
    
    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void onTick() override;
};

template <>
struct ModuleTraits<TestMod> {
    static constexpr std::string_view Category = "Misc";
};