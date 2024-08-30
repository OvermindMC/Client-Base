#include "ClickGui.h"

class Window {
public:
    virtual ~Window() = default;

    struct TitleData {
        std::string text;
        ImColor titleColor;

        TitleData(std::string display_text, ImColor title_color) : text(display_text), titleColor(title_color) {};
    };

    Window(TitleData tData, float font_size, ImVec2 target_pos) : titleData(tData), fontSize(font_size), targetPos(target_pos) {
        //
    };

    TitleData getTitle() const {
        return this->titleData;
    };

    ImVec2 getPos() const {
        return this->targetPos;
    };

    float getFontSize() const {
        return this->fontSize;
    };

    ImVec2 getTitleSize() const {
        ImVec2 curr = Renderer::GetTextSize(this->titleData.text, this->fontSize);
        curr = ImVec2(this->targetPos.x + curr.x, this->targetPos.y + curr.y);

        curr.x += 8.f, curr.y += 6.f;

        return curr;
    };

    ImVec2 getSize() const {
        ImVec2 curr = this->getTitleSize();

        //

        return curr;
    };

    void renderTitle() {
        ImVec2 pos = this->getPos();
        ImVec2 size = this->getTitleSize();
        Window::TitleData title = this->getTitle();

        Renderer::FillRect(
            ImVec4(
                pos.x, pos.y, size.x, size.y
            ), title.titleColor, 1.f
        );

        ImVec2 titleSize = Renderer::GetTextSize(
            title.text, this->getFontSize()
        );

        Renderer::RenderText(
            ImVec2(
                pos.x + (((size.x - pos.x) / 2.f) - titleSize.x / 2.f), pos.y + (((size.y - pos.y) / 2.f) - titleSize.y / 2.f)
            ), title.text, this->getFontSize(), ImColor(255.f, 255.f, 255.f)
        );
    };

    void renderBody() {
        //
    };

    void updateIntersects(ImVec2 point) {
        ImVec2 pos = this->getPos();
        ImVec2 size = this->getTitleSize();

        ImVec4 titleRect = ImVec4(
            pos.x, pos.y, size.x, size.y
        );
        
        this->titleData.titleColor.Value.w = (
            titleRect.x < point.x && titleRect.y < point.y && titleRect.z > point.x && titleRect.w > point.y ? 0.3 : 1.f
        );
    };
private:
    TitleData titleData;
    ImVec2 targetPos;
    float fontSize;
};

ClickGui::ClickGui(Category* c) : Module(c) {
    this->setBind(VK_INSERT);

    static std::vector<std::unique_ptr<Window>> windows;

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

            if(windows.empty()) {
                ImVec2 currPos = ImVec2(2.f, 10.f);
                for(const auto& category : this->getMgr()->getCategories()) {
                    auto window = std::make_unique<Window>(
                        Window::TitleData(
                            category->getName(), ImColor(50.f, 90.f, 110.f)
                        ), 19.f, currPos
                    );
                    currPos.x = (window->getTitleSize().x + 2.f);
                    windows.push_back(std::move(window));
                };
            };

            for(const auto& window : windows) {
                window->renderTitle();
            };
        }
    );

    this->registerEvent<EventBase::Type::onKey, EventBase::Priority::High, uint64_t, bool, bool&>(
        [&](uint64_t key, bool isDown, bool& cancel) {
            cancel = true;
        }
    );

    this->registerEvent<EventBase::Type::onMouse, EventBase::Priority::High, char, bool, Vec2<int>, bool&>(
        [&](char action, bool isDown, Vec2<int> mousePos, bool& cancel) {
            cancel = true;

            for(const auto& window : windows) {
                window->updateIntersects(
                    ImVec2(
                        mousePos.x, mousePos.y
                    )
                );
            };

            /*for(const auto& el : elements) {
                el->isIntersected = (
                    el->rect.x < mousePos.x && el->rect.y < mousePos.y && el->rect.z > mousePos.x && el->rect.w > mousePos.y
                );
            };*/
        }
    );
};

std::string ClickGui::getName() const {
    return "Click GUI";
};