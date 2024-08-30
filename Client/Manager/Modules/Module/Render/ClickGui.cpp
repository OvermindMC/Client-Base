#include "ClickGui.h"

ClickGui::ClickGui(Category* c) : Module(c) {
    this->setBind(VK_INSERT);

    this->registerEvent<EventBase::Type::onDisable, EventBase::Priority::High>(
        [&]() {
            if(this->blurProg.first > 0.f) {
                this->blurProg.second = 0.f;
                this->setIsEnabled(true);
            } else {
                this->blurProg.second = .2f;
            };
        }
    );

    this->registerEvent<EventBase::Type::onRender, EventBase::Priority::High>(
        [&]() {
            auto& io = ImGui::GetIO();
            ImVec2 display = io.DisplaySize;

            Utils::reachOffset(&blurProg.first, blurProg.second, (io.DeltaTime * 1000.f) * 0.002f);

            OverFX::CreateBlur(
                ImVec4(
                    0.f, 0.f, display.x, display.y
                ), blurProg.first
            );

            if(blurProg.first <= 0.f) {
                return this->setIsEnabled(false);
            };
        }
    );

    this->registerEvent<EventBase::Type::onKey, EventBase::Priority::High, uint64_t, bool, bool&>(
        [&](uint64_t key, bool isDown, bool& cancel) {
            cancel = true;
        }
    );
};

std::string ClickGui::getName() const {
    return "Click GUI";
};