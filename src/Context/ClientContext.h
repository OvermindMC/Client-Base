#pragma once

#include <vector>
#include <memory>

#include "Event/Event.h"
#include "Event/Dispatcher.h"

class Client;
class BaseHook;
class Category;

class ClientContext {
public:
    explicit ClientContext(Client*) noexcept;
    ~ClientContext() noexcept;

    ClientContext(const ClientContext&) = delete;
    ClientContext& operator=(const ClientContext&) = delete;

    Client* getClient() const noexcept;
    EventDispatcher& getEvents() noexcept;

    bool IsShuttingDown() const noexcept;

    template<typename T>
    void RegisterModule() noexcept;

    template<typename T>
    void RegisterHook() noexcept;
private:
    Client* clientPtr;
    bool mMhInit = false;

    EventDispatcher mDispatcher;
    std::vector<std::unique_ptr<BaseHook>> mHooks;
    std::vector<std::unique_ptr<Category>> mCategories;
};