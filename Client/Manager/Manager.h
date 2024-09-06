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

    template<typename T>
    void dispatchEvent(const T& event, std::function<bool(Module*)> filter = nullptr) {
        std::vector<std::pair<EventPriority, Event<T>*>> sorted_events;

        for (const auto& [type, category] : this->categories) {
            auto modules = category->getModules();

            if (filter) {
                modules.erase(
                    std::remove_if(
                        modules.begin(), modules.end(), [&](Module* m) {
                            return !filter(m);
                        }
                    ), modules.end()
                );
            };

            for (const auto mod : modules) {
                auto [eventList, priorityList] = mod->getEvents<T>();
                for (size_t i = 0; i < eventList.size(); ++i) {
                    sorted_events.emplace_back(priorityList[i], eventList[i]);
                };
            };
        };

        std::sort(sorted_events.begin(), sorted_events.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        for (const auto& [priority, eventPtr] : sorted_events) {
            if (auto specificEvent = dynamic_cast<Event<T>*>(eventPtr)) {
                specificEvent->call(event);
            } else {
                //
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