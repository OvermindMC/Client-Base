#include "ClickGui.h"

class Window {
public:
    virtual ~Window() = default;

    struct TitleData {
        std::string text;
        ImColor titleColor;

        TitleData(std::string display_text, ImColor title_color) : text(display_text), titleColor(title_color) {};
    };

    struct BodyStyle {
        ImColor bgColor = ImColor(21.f, 21.f, 21.f);

        BodyStyle(ImColor background_color) : bgColor(background_color) {};
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

            bool isExpanded(char state = -1) {
                if(state != -1) {
                    this->isElExpanded = state;
                };
                return this->isElExpanded;
            };

            float animProg = 0.f;
        private:
            Module* mod = nullptr;
            bool isElExpanded = false;
    };

    Window(TitleData tData, BodyStyle style, float font_size, ImVec2 target_pos) : titleData(tData), bodyStyle(style), fontSize(font_size), targetPos(target_pos) {
        //
    };

    TitleData& getTitle() {
        return this->titleData;
    };

    BodyStyle& getStyle() {
        return this->bodyStyle;
    };

    ImVec2 getPos() const {
        return this->targetPos;
    };

    void setPos(const ImVec2& pos) {
        this->targetPos = pos;
    };

    float getFontSize() const {
        return this->fontSize;
    };

    void setFontSize(float const& font_size) {
        this->fontSize = font_size;
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

        curr.x += this->padd.x, curr.y += (this->padd.y / 2.f);

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

    ImVec4 getBodyRect() const {
        ImVec2 titleSize = this->getTitleSize();
        ImVec2 size = this->getSize();
        return ImVec4(
            this->targetPos.x, titleSize.y,
            titleSize.x, size.y
        );
    };

    void renderTitle() {
        ImVec2 pos = this->getPos();
        ImVec2 size = this->getTitleSize();
        Window::TitleData title = this->getTitle();

        Renderer::FillRect(
            ImVec4(
                pos.x, pos.y, size.x, size.y
            ), title.titleColor, this->rounding
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

    void renderBody(float deltaMultiplier = 1.f) {
        ImVec2 bodyPos = this->getSize();
        ImVec2 titleSize = this->getTitleSize();
        ImVec2 startPos = ImVec2(this->targetPos.x, titleSize.y);
        
        BodyStyle& style = this->getStyle();

        ImVec4 targetRect = ImVec4(
            startPos.x,
            this->targetPos.y,
            bodyPos.x, startPos.y + (bodyPos.y - startPos.y) * this->expandProg
        );

        Utils::reachOffset(
            &this->expandProg,
            this->isExpanded() ? 1.f : 0.f, 0.01f * deltaMultiplier
        );

        Renderer::FillRect(
            targetRect, style.bgColor, this->rounding
        );

        float yOff = (startPos.y + this->padd.y);
        for(const auto& el : this->elements) {
            ImVec2 elSize = el->getSize();
            auto style = el->getStyle();

            ImVec4 elRect = ImVec4(
                startPos.x + 2.f, yOff - (this->padd.y / (2.f + (this->fontSize / 10.f))),
                titleSize.x - 2.f, (yOff + elSize.y) + (this->padd.y  / (2.f + (this->fontSize / 10.f)))
            );

            if (elRect.w > targetRect.w)
                break;
            
            std::string displayText = el->getText();
            
            if(el->isType<Window::ModuleElement>()) {
                auto casted = dynamic_cast<Window::ModuleElement*>(el.get());
                auto mod = casted ? casted->getModule() : nullptr;

                if(mod) {
                    Utils::reachOffset(&casted->animProg, mod->isEnabled() ? 1.f : 0.f, 0.01f * deltaMultiplier);

                    if(casted->animProg > 0.f) {
                        Renderer::FillRect(
                            ImVec4(
                                elRect.x + ((elRect.z - elRect.x) * (1.f - casted->animProg)) / 2.f, 
                                elRect.y + ((elRect.w - elRect.y) * (1.f - casted->animProg)) / 2.f, 
                                elRect.z - ((elRect.z - elRect.x) * (1.f - casted->animProg)) / 2.f, 
                                elRect.w - ((elRect.w - elRect.y) * (1.f - casted->animProg)) / 2.f
                            ), ImColor(50.f, 50.f, 50.f), this->rounding / 2.f
                        );
                    };
                };

                std::string expText = casted->isExpanded() ? "-" : "+";
                float expTxtLen = Renderer::GetTextSize(expText, this->fontSize).x;

                Renderer::RenderText(
                    ImVec2(
                        targetRect.z - (expTxtLen * 2.f), yOff
                    ), expText, this->fontSize, style.textColor
                );
            };

            Renderer::RenderText(
                ImVec2(
                    startPos.x + (((titleSize.x - startPos.x) / 2.f) - elSize.x / 2.f), yOff
                ), el->getText(), this->fontSize, style.textColor
            );

            yOff += (elSize.y + this->padd.y);
        };
    };

    void updateIntersects(ImVec2 point, float deltaMultiplier = 1.f) {
        auto& io = ImGui::GetIO();
        
        ImVec2 pos = this->getPos();
        ImVec2 size = this->getTitleSize();

        ImVec4 titleRect = ImVec4(
            pos.x, pos.y, size.x, size.y
        );

        this->isIntersected(titleRect.x < point.x && titleRect.y < point.y && titleRect.z > point.x && titleRect.w > point.y);
        
        Utils::reachOffset(
            &this->titleData.titleColor.Value.w,
            titleRect.x < point.x && titleRect.y < point.y && titleRect.z > point.x && titleRect.w > point.y ? 0.6 : 1.f, 0.01f * deltaMultiplier
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

            if (yOff + elSize.y <= startPos.y + (bodyPos.y - startPos.y) * this->expandProg) {
                el->isIntersected(elRect.x < point.x && elRect.y < point.y && elRect.z > point.x && elRect.w > point.y);
                Utils::reachOffset(
                    &style.textColor.Value.w,
                    el->isIntersected() ? 0.7f : 1.f, 0.01f * deltaMultiplier
                );
            } else {
                el->isIntersected(false);
            };

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

    bool isExpanded(char state = -1) {
        if(state != -1) {
            this->isWindowExpanded = state;
        };
        return this->isWindowExpanded;
    };

    bool isIntersected(char state = -1) {
        if(state != -1) {
            this->isTitleIntersected = state;
        };
        return this->isTitleIntersected;
    };
private:
    TitleData titleData;
    BodyStyle bodyStyle;
    ImVec2 targetPos;
    
    float fontSize;
    float rounding = 5.f;
    float expandProg = 0.f;
    bool isTitleIntersected;
    bool isWindowExpanded = true;
    ImVec2 padd = ImVec2(8.f, 6.f);

    std::vector<std::unique_ptr<Element>> elements;
};

ClickGui::~ClickGui() {
    this->revert();
};

ClickGui::ClickGui(Category* c) : Module(c) {
    this->setBind(VK_INSERT);
    this->needsEvents(true);

    static std::vector<std::unique_ptr<Window>> windows;
    static ImVec2 lastMousePos;

    this->registerEvent<EventBase::Type::onRender, EventBase::Priority::High>(
        [&]() {
            auto& io = ImGui::GetIO();
            this->deltaMultiplier = io.Framerate / 60.f;

            ImVec2 display = io.DisplaySize;

            static float prevBlurV = blurProg.first;

            blurProg.second = (this->isEnabled() ? 2.f : 0.f);
            Utils::reachOffset(&blurProg.first, blurProg.second, 0.01f * this->deltaMultiplier);

            if(prevBlurV > 0.f && blurProg.first <= 0.f) {
                this->revert();
            };

            prevBlurV = blurProg.first;

            if(this->blurProg.first <= 0.f)
                return;

            OverFX::CreateBlur(
                ImVec4(
                    0.f, 0.f, display.x, display.y
                ), blurProg.first / 10.f
            );

            ClientInstance* ci = MC::getClientInstance();
            GuiData* guidata = ci ? ci->getGuiData() : nullptr;
            
            ci->releaseMouse();

            if(!guidata)
                return;
            
            float fontSize = (guidata->uiScale <= 1 ? 16.f : guidata->uiScale * 9.f);

            if(windows.empty()) {
                auto categories = this->getMgr()->getCategories();

                float totalWidth = 0.f;
                std::vector<ImVec2> windowSizes;
                ImVec2 padding = ImVec2(guidata->uiScale <= 1 ? 60.f : 150.f, 20.f);
                
                for(const auto& category : categories) {
                    auto window = std::make_unique<Window>(
                        Window::TitleData(
                            category->getName(), ImColor(50.f, 50.f, 130.f)
                        ), Window::BodyStyle(
                            ImColor(30.f, 30.f, 30.f)
                        ), fontSize, ImVec2(0.f, 0.f)
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

                    window->setPad(padding);
                    ImVec2 size = window->getTitleSize();
                    totalWidth += size.x;
                    windowSizes.push_back(size);
                    windows.push_back(std::move(window));
                };

                totalWidth += (windows.size() - 1) * 2.f;

                float startX = (display.x - totalWidth) / 2.f;
                float currentX = startX;

                for (size_t i = 0; i < windows.size(); ++i) {
                    windows[i]->setPos(ImVec2(currentX, 10.f));
                    currentX += windowSizes[i].x + 2.f;
                };
            };

            for(const auto& window : windows) {
                if(window->getFontSize() != fontSize) {
                    return windows.clear();
                };
                window->updateIntersects(lastMousePos, this->deltaMultiplier);
                window->renderBody(this->deltaMultiplier);
                window->renderTitle();
            };
        }
    );

    this->registerEvent<EventBase::Type::onKey, EventBase::Priority::High, uint64_t, bool, bool&>(
        [&](uint64_t key, bool isDown, bool& cancel) {
            if(!this->isEnabled())
                return;
            
            cancel = true;
        }
    );

    this->registerEvent<EventBase::Type::onMouse, EventBase::Priority::High, char, bool, Vec2<int>, bool&>(
        [&](char action, bool isDown, Vec2<int> mousePos, bool& cancel) {
            if(!this->isEnabled())
                return;
            
            cancel = true;

            lastMousePos = ImVec2(
                mousePos.x, mousePos.y
            );

            auto& io = ImGui::GetIO();
            bool doneAction = false;
            for(auto iter = windows.rbegin(); iter != windows.rend(); ++iter) {
                const auto& window = (*iter).get();
                if(doneAction) break;
                if(window->isIntersected()) {
                    if(isDown) {
                        if(action == 1 && this->dragStart == Vec2<float>()) {
                            this->dragStart = Vec2<float>(mousePos.x, mousePos.y);
                        } else if(action == 2) {
                            window->isExpanded(!window->isExpanded());
                        };
                    };
                    if(this->dragStart != Vec2<float>()) {
                        Vec2<float> pos = Vec2<float>(mousePos.x, mousePos.y);
                        Vec2<float> dragOffset = pos - this->dragStart;

                        ImVec2 newPos = window->getPos();
                        newPos.x += dragOffset.x;
                        newPos.y += dragOffset.y;
                        window->setPos(newPos);
                        
                        this->dragStart = Vec2<float>(mousePos.x, mousePos.y);
                    };
                    doneAction = true;
                };
                for(const auto& el : window->getElements()) {
                    if(doneAction) break;
                    if(el->isIntersected()) {
                        if(el->isType<Window::ModuleElement>()) {
                            auto casted = dynamic_cast<Window::ModuleElement*>(el);
                            auto mod = casted ? casted->getModule() : nullptr;
                            
                            if(isDown && action == 1) {
                                if(mod)
                                    mod->toggleIsEnabled();
                            } else if(isDown && action == 2) {
                                casted->isExpanded(!casted->isExpanded());
                            };
                        };
                        doneAction = true;
                    };
                };

                if(!isDown && action == 1) {
                    this->dragStart = Vec2<float>();
                };
            };
        }
    );
};

std::string ClickGui::getName() const {
    return "Click GUI";
};

void ClickGui::revert() {
    ClientInstance* ci = MC::getClientInstance();
    std::string screenName = ci ? ci->getTopScreenName() : "";

    if(screenName.rfind("hud_screen") != std::string::npos) {
        ci->grabMouse();
    };
};