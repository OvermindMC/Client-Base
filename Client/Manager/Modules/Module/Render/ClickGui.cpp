#include "ClickGui.h"

class Window {
public:
    virtual ~Window() = default;

    struct TitleData {
        std::string text;
        ImColor titleColor;

        TitleData(std::string display_text, ImColor title_color) : text(display_text), titleColor(title_color) {};
    };

    class Element {
        public:
            virtual ~Element() = default;

            struct Style {
                ImColor textColor = ImColor(255.f, 255.f, 255.f);
            };

            Element(Window* window, std::string display_text) : parent(window), elementText(display_text) {
                //
            };

            ImVec2 getSize() const {
                return Renderer::GetTextSize(
                    this->elementText, this->parent->getFontSize()
                );
            };

            std::string getText() const {
                return this->elementText;
            };

            Style& getStyle() {
                return this->elStyle;
            };

            bool isIntersected(char state = -1) {
                if(state != -1) {
                    this->intersected = state;
                };
                return this->intersected;
            };

            template<std::derived_from<Element> T>
            bool isType() const {
                return dynamic_cast<const T*>(this) != nullptr;
            };
        private:
            Window* parent = nullptr;
            std::string elementText;
            bool intersected;
            Style elStyle;
    };

    class ModuleElement : public Element {
        public:
            ModuleElement(Window* window, Module* m) : Element(window, m->getName()), mod(m) {};

            Module* getModule() const {
                return this->mod;
            };
        private:
            Module* mod = nullptr;
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

    ImVec2 getPad() const {
        return this->padd;
    };

    void setPad(const ImVec2& pad) {
        this->padd = pad;
    };

    ImVec2 getTitleSize() const {
        ImVec2 curr = Renderer::GetTextSize(this->titleData.text, this->fontSize);
        curr = ImVec2(this->targetPos.x + curr.x, this->targetPos.y + curr.y);

        for(const auto& el : this->elements) {
            ImVec2 elSize = el->getSize();

            if(this->targetPos.x + elSize.x > curr.x) {
                curr.x = (this->targetPos.x + elSize.x);
            };
        };

        curr.x += this->padd.x, curr.y += this->padd.y;

        return curr;
    };

    ImVec2 getSize() const {
        ImVec2 curr = this->getTitleSize();

        for(const auto& el : this->elements) {
            ImVec2 elSize = el->getSize();

            curr.y += (elSize.y + this->padd.y);
        };

        curr.y += this->padd.y;
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
        ImVec2 bodyPos = this->getSize();
        ImVec2 titleSize = this->getTitleSize();
        ImVec2 startPos = ImVec2(this->targetPos.x, titleSize.y);
        
        Renderer::FillRect(
            ImVec4(
                startPos.x, startPos.y,
                bodyPos.x, bodyPos.y
            ), ImColor(21.f, 21.f, 21.f), 1.f
        );

        float yOff = (startPos.y + this->padd.y);
        for(const auto& el : this->elements) {
            ImVec2 elSize = el->getSize();
            auto style = el->getStyle();

            Renderer::RenderText(
                ImVec2(
                    startPos.x + (((titleSize.x - startPos.x) / 2.f) - elSize.x / 2.f), yOff
                ), el->getText(), this->fontSize, style.textColor
            );

            yOff += (elSize.y + this->padd.y);
        };
    };

    void updateIntersects(ImVec2 point) {
        auto& io = ImGui::GetIO();
        
        ImVec2 pos = this->getPos();
        ImVec2 size = this->getTitleSize();

        ImVec4 titleRect = ImVec4(
            pos.x, pos.y, size.x, size.y
        );
        
        Utils::reachOffset(
            &this->titleData.titleColor.Value.w,
            titleRect.x < point.x && titleRect.y < point.y && titleRect.z > point.x && titleRect.w > point.y ? 0.6 : 1.f, (io.DeltaTime * 1000.f) * 0.002f
        );

        ImVec2 bodyPos = this->getSize();
        ImVec2 titleSize = this->getTitleSize();
        ImVec2 startPos = ImVec2(this->targetPos.x, titleSize.y);

        float yOff = (startPos.y + this->padd.y);
        for(const auto& el : this->elements) {
            ImVec2 elSize = el->getSize();
            auto& style = el->getStyle();

            ImVec4 elRect = ImVec4(
                startPos.x + 2.f, yOff,
                titleSize.x - 2.f, yOff + elSize.y
            );

            el->isIntersected(elRect.x < point.x && elRect.y < point.y && elRect.z > point.x && elRect.w > point.y);
            Utils::reachOffset(
                &style.textColor.Value.w,
                el->isIntersected() ? 0.7f : 1.f, (io.DeltaTime * 1000.f) * 0.002f
            );

            yOff += (elSize.y + this->padd.y);
        };
    };

    void addElement(std::unique_ptr<Element> el) {
        this->elements.push_back(std::move(el));
    };

    std::vector<Element*> getElements() const {
        std::vector<Element*> list;

        for(const auto& el : this->elements) {
            list.push_back(el.get());
        };

        return list;
    };
private:
    TitleData titleData;
    ImVec2 targetPos;
    
    float fontSize;
    ImVec2 padd = ImVec2(8.f, 6.f);

    std::vector<std::unique_ptr<Element>> elements;
};

ClickGui::ClickGui(Category* c) : Module(c) {
    this->setBind(VK_INSERT);

    static std::vector<std::unique_ptr<Window>> windows;
    static ImVec2 lastMousePos;

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
                float fontSize = 16.f;

                for(const auto& category : this->getMgr()->getCategories()) {
                    auto window = std::make_unique<Window>(
                        Window::TitleData(
                            category->getName(), ImColor(50.f, 90.f, 110.f)
                        ), fontSize, currPos
                    );

                    auto mods = category->getModules();
                    std::sort(mods.begin(), mods.end(), [&](Module* a, Module* b){
                        return Renderer::GetTextSize(a->getName(), fontSize).x < Renderer::GetTextSize(b->getName(), fontSize).x;
                    });

                    for(const auto& mod : mods) {
                        window->addElement(
                            std::make_unique<Window::ModuleElement>(
                                window.get(), mod
                            )
                        );
                    };

                    window->setPad(ImVec2(20.f, 8.f));

                    currPos.x = (window->getSize().x + 2.f);
                    windows.push_back(std::move(window));
                };
            };

            for(const auto& window : windows) {
                window->updateIntersects(lastMousePos);
                window->renderTitle();
                window->renderBody();
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

            lastMousePos = ImVec2(
                mousePos.x, mousePos.y
            );

            auto& io = ImGui::GetIO();
            bool doneAction = false;
            for(const auto& window : windows) {
                if(doneAction) break;
                for(const auto& el : window->getElements()) {
                    if(doneAction) break;
                    if(el->isIntersected()) {
                        if(isDown && action == 1) {
                            if(el->isType<Window::ModuleElement>()) {
                                auto mod = dynamic_cast<Window::ModuleElement*>(el)->getModule();

                                if(mod)
                                    mod->toggleIsEnabled();
                            };
                            doneAction = true;
                        };
                    };
                };
            };
        }
    );
};

std::string ClickGui::getName() const {
    return "Click GUI";
};