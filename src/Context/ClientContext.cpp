#include "ClientContext.h"

#include "../Client.h"
#include "Hook/Hook.h"
#include "Category/Category.h"
#include "Category/Module/Module.h"

#include "Category/Module/Modules/Other/TestMod.h"

#include "Hook/Hooks/UIRenderCtx.h"

ClientContext::ClientContext(Client* client) noexcept : clientPtr(client) {
    if(MH_Initialize() != MH_OK) {
        if(Client* client = getClient()) {
            client->PushReq(
                Client::ClientRequest::ShutDown(
                    1, "Failed to initialize MinHook!"
                )
            );
        };
    } else {
        mMhInit = true;
        if(Client* client = getClient()) {
            client->PushReq(
                Client::ClientRequest::Log(
                    "Successfully initialized MinHook!"
                )
            );
        };
    };
    
    RegisterHook<UIRenderCtxHook>();

    RegisterModule<TestMod>();
};

ClientContext::~ClientContext() noexcept {
    if(mMhInit) {
        this->mHooks.clear();
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
    };
    
    this->mCategories.clear();
    getEvents().Clear();
};

Client* ClientContext::getClient() const noexcept {
    return clientPtr;
};

EventDispatcher& ClientContext::getEvents() noexcept {
    return mDispatcher;
};

bool ClientContext::IsShuttingDown() const noexcept {
    if(Client* client = getClient()) {
        return !client->IsRunning();
    };
    return false;
};

template<typename T>
void ClientContext::RegisterModule() noexcept {
    static_assert(std::is_base_of_v<Module, T>, "RegisterModule<T>: T must derive from Module");
    constexpr auto catName = ModuleTraits<T>::Category;

    auto iter = std::find_if(
        mCategories.begin(), mCategories.end(), [&](auto& ptr) {
            return ptr->getName() == catName;
        }
    );

    Category* category = nullptr;

    if(iter == mCategories.end()) {
        auto cat = std::make_unique<Category>(this, std::string(catName));
        category = cat.get();

        mCategories.emplace_back(std::move(cat));
    } else {
        category = iter->get();
    };

    category->addModule(
        std::make_unique<T>(category)
    );
};

template<typename T>
void ClientContext::RegisterHook() noexcept {
    static_assert(std::is_base_of_v<BaseHook, T>, "RegisterHook<T>: T must derive from BaseHook");

    try {
        mHooks.emplace_back(
            std::make_unique<T>(
                this
            )
        );
    } catch(...) {
        if(Client* client = getClient()) {
            client->PushReq(
                Client::ClientRequest::Log(
                    "Failed to initialize hook: " + std::string(HookTraits<T>::Name)
                )
            );
        };
    };
};