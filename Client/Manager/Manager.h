#pragma once

#include "../Client.h"

#include "Event/Dispatcher.h"
#include "Sigs/Sig.h"

class BaseHook;
class Category;
class Module;

class Manager {
public:
    Manager(Client*);
    ~Manager();
    
    Client* getClient();
    
    bool isTicking() const;
    void stop();

    template<class C>
    void registerHook();

    template<typename C, typename T>
    T getSig();

    template<class C>
    C* getCategory();

    std::vector<Category*> getCategories() const;

    template<class C, class M>
    void registerMod();

    template<EventBase::Type T, typename... Args>
    void dispatchEvent(Args... args) {
        std::vector<EventBase*> list;

        for(const auto& [ type, category ] : this->categories) {
            for(const auto mod : category->getModules()) {
                for(const auto ev : mod->getEvents<T>()) {
                    list.push_back(ev);
                };
            };
        };

        std::sort(list.begin(), list.end(), [](EventBase* a, EventBase* b) {
            return a->getPriority() > b->getPriority();
        });

        for (auto& event : list) {
            if (auto specificEvent = dynamic_cast<Event<T, EventBase::Priority::Low, Args...>*>(event)) {
                specificEvent->call(std::forward<Args>(args)...);
            }
            else if (auto specificEvent = dynamic_cast<Event<T, EventBase::Priority::Medium, Args...>*>(event)) {
                specificEvent->call(std::forward<Args>(args)...);
            }
            else if (auto specificEvent = dynamic_cast<Event<T, EventBase::Priority::High, Args...>*>(event)) {
                specificEvent->call(std::forward<Args>(args)...);
            };
        };
    };
private:
    Client* ciPtr = nullptr;
    bool isTickingState = false;
    std::vector<std::unique_ptr<BaseHook>> hooks;
    std::map<std::string, std::unique_ptr<BaseSig>> sigMap;
    std::map<std::string, std::unique_ptr<Category>> categories;
};