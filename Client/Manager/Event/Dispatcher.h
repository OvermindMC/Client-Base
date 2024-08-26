#pragma once

#include "Event.h"

class Module;

class EventHandler {
public:
    virtual ~EventHandler() = default;

    EventHandler(Module* m) : parent(m) {};

    template<EventBase::Type T, EventBase::Priority P, typename... Args>
    void registerEvent(std::function<void(Args...)> callback) {
        std::unique_ptr<Event<T, P, Args...>> event = std::make_unique<Event<T, P, Args...>>(callback);
        this->events.at(T).emplace_back(std::move(event));
    };

    template<typename EventBase::Type T>
    void unregisterEvents() {
        auto iter = events.at(T);
        iter.clear();
    };

    template<EventBase::Type T>
    std::vector<EventBase*> getEvents() const {
        std::vector<EventBase*> list;

        if(this->events.contains(T)) {
            for(const auto& event : this->events.at(T)) {
                list.emplace_back(event.get());
            };
        };

        return list;
    };
private:
    Module* parent = nullptr;
    std::map<EventBase::Type, std::vector<std::unique_ptr<EventBase>>> events;
};