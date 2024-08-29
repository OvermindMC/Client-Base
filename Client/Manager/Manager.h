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
    void dispatchEvent(Args... args, std::function<bool(Module*)> filter = nullptr) {
        std::vector<EventBase*> list;

        for(const auto& [ type, category ] : this->categories) {
            auto modules = category->getModules();

            if(filter) {
                modules.erase(
                    std::remove_if(
                        modules.begin(), modules.end(), [&](Module* m) {
                            return !filter(m);
                        }
                    ), modules.end()
                );
            };

            for(const auto mod : modules) {
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

    bool isUsingKey(uint64_t winKeyId, uint8_t state = -1) {
        if (state != -1) {
            keyMap[winKeyId] = (state != 0);
            return false;
        } else {
            auto it = keyMap.find(winKeyId);
            if (it != keyMap.end()) {
                return it->second;
            };
            return false;
        };
    };
private:
    Client* ciPtr = nullptr;
    bool isTickingState = false;
    std::map<uint64_t, bool> keyMap;
    std::vector<std::unique_ptr<BaseHook>> hooks;
    std::map<std::string, std::unique_ptr<BaseSig>> sigMap;
    std::map<std::string, std::unique_ptr<Category>> categories;
};