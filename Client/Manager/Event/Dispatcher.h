#pragma once

#include "Event.h"

enum class EventPriority : int {
    Low = 1, Medium = 2, High = 3
};

class EventHandler {
public:
    virtual ~EventHandler() = default;

    template<typename T, EventPriority P>
    void registerEvent(typename Event<T>::CallbackType callback) {
        auto event = std::make_unique<Event<T>>(callback);
        events_[typeid(T)].emplace_back(P, std::move(event));
    };

    template<typename T>
    void dispatchEvent(const T& event) {
        auto it = events_.find(typeid(T));
        if (it != events_.end()) {
            std::sort(it->second.begin(), it->second.end(), [](const auto& a, const auto& b) {
                return a.first > b.first;
            });

            for (const auto& [priority, eventBase] : it->second) {
                if (auto specificEvent = dynamic_cast<Event<T>*>(eventBase.get())) {
                    specificEvent->call(event);
                };
            };
        };
    };

    template<typename T>
    std::pair<std::vector<Event<T>*>, std::vector<EventPriority>> getEvents() const {
        std::vector<Event<T>*> eventList;
        std::vector<EventPriority> priorityList;
        auto it = events_.find(typeid(T));
        if (it != events_.end()) {
            for (const auto& [priority, eventBase] : it->second) {
                if (auto specificEvent = dynamic_cast<Event<T>*>(eventBase.get())) {
                    eventList.push_back(specificEvent);
                    priorityList.push_back(priority);
                }
            }
        }
        return { eventList, priorityList };
    };
private:
    std::map<std::type_index, std::vector<std::pair<EventPriority, std::unique_ptr<EventBase>>>> events_;
};