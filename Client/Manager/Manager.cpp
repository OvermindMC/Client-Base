#include "Manager.h"
#include "Event/Dispatcher.h"

#include "Hooks/Subs/Key_Input.h"
#include "Hooks/Subs/Mouse_Input.h"
#include "Hooks/Subs/Actor_Lerp.h"
#include "Hooks/Subs/Level_Tick.h"
#include "Hooks/Subs/Present_Tick.h"

#include "Modules/Module/Combat/Parent.h"
#include "Modules/Module/Movement/Parent.h"
#include "Modules/Module/Render/ClickGui.h"
#include "Modules/Module/Other/Parent.h"

Manager::Manager(Client* client_ptr) : ciPtr(client_ptr) {
    if(MH_Initialize() == MH_OK) {
        SwapChainStub::init();
        
        this->registerHook<KeyInput_Hook>();
        this->registerHook<MouseInput_Hook>();
        this->registerHook<ActorLerp_Hook>();
        this->registerHook<LevelTick_Hook>();
        this->registerHook<PresentTick_Hook>();
    };

    this->registerMod<Combat, Killaura>();
    
    this->registerMod<Move, AutoSprint>();
    this->registerMod<Move, FastSneak>();
    this->registerMod<Move, Velocity>();
    this->registerMod<Move, NoSlow>();

    this->registerMod<Render, ClickGui>();
    
    this->registerMod<Other, Uninject>();
    this->registerMod<Other, TestMod>();

    this->isTickingState = true;

    while(this->isTickingState) {
        for(auto& [ name, category ] : this->categories) {
            for(const auto mod : category->getModules()) {
                mod->baseTick();
            };
        };
        Sleep(1);
    };
};

Manager::~Manager() {
    this->hooks.clear();
    this->sigMap.clear();
    this->categories.clear();

    SwapChainStub::free();

    Renderer::CleanUp(true);
    OverFX::CleanUp(true);

    MH_DisableHook(MH_ALL_HOOKS);
    std::this_thread::yield();
    MH_Uninitialize();
};

Client* Manager::getClient() {
    return this->ciPtr;
};

bool Manager::isTicking() const {
    return this->isTickingState;
};

void Manager::stop() {
    if(this->isTickingState) {
        this->isTickingState = false;
    };
};

template<class C>
void Manager::registerHook() {
    static_assert(std::is_base_of<BaseHook, C>::value, "Template Class type must derive from BaseHook");

    auto hook = std::make_unique<C>(this);
    this->hooks.push_back(std::move(hook));
};

template<typename C, typename T>
T Manager::getSig() {
    static_assert(std::is_base_of<BaseSig, C>::value, "Template Class type must derive from BaseSig");

    std::string name = C().getName();
    
    auto iter = this->sigMap.find(name);
    if(iter == this->sigMap.end()) {
        auto sig = std::make_unique<C>();
        iter = this->sigMap.emplace(name, std::move(sig)).first;
    };

    return dynamic_cast<C*>(iter->second.get())->get();
};

template<class C>
C* Manager::getCategory() {
    static_assert(std::is_base_of<Category, C>::value, "Template Class type must derive from Category");

    std::string name = C(this).getName();
    
    auto iter = this->categories.find(name);
    if(iter == this->categories.end()) {
        auto c = std::make_unique<C>(this);
        iter = this->categories.emplace(name, std::move(c)).first;
    };

    return dynamic_cast<C*>(iter->second.get());
};

std::vector<Category*> Manager::getCategories() const {
    std::vector<Category*> list;

    for(auto& [ name, category ] : this->categories) {
        list.push_back(category.get());
    };

    return list;
};

template<class C, class M>
void Manager::registerMod() {
    static_assert(std::is_base_of<Category, C>::value, "Template Class type must derive from Category");
    static_assert(std::is_base_of<Module, M>::value, "Template Class type must derive from Module");

    C* category = this->getCategory<C>();

    if(category) {
        category->registerMod<M>();
    };
};