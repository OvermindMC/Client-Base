#include "Manager.h"

#include "Hooks/Subs/Level_Tick.h"
#include "Hooks/Subs/Present_Tick.h"

#include "Modules/Module/Other/Parent.h"

Manager::Manager(Client* client_ptr) : ciPtr(client_ptr) {
    if(MH_Initialize() == MH_OK) {
        this->registerHook<LevelTick_Hook>();
        this->registerHook<PresentTick_Hook>();
    };

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

    Sleep(10);
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

    std::string name = C(this).getName();

    auto iter = std::find_if(this->hooks.begin(), this->hooks.end(), [&](const std::unique_ptr<BaseHook>& hook) {
        return hook.get()->getName() == name;
    });

    if(iter == this->hooks.end()) {
        auto hook = std::make_unique<C>(this);
        this->hooks.push_back(std::move(hook));
    } else {
        Debugger::log("Hook " + name + " has already been initialized!");
    };
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
