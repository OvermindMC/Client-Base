#pragma once

#include "Event.h"

class Module;

class EventHandler {
public:
    virtual ~EventHandler() = default;

    EventHandler(Module* m) : parent(m) {};

    template<EventBase::Type T, EventBase::Priority P, typename... Args>
    void registerEvent(std::function<void(Args...)> callback) {
        auto event = std::make_unique<Event<T, P, Args...>>(callback);
        this->events[T].emplace_back(std::move(event));
    };

    template<EventBase::Type T, EventBase::Priority P>
    void registerEvent(std::function<void()> callback) {
        auto event = std::make_unique<Event<T, P>>(callback);
        this->events[T].emplace_back(std::move(event));
    };

    template<typename EventBase::Type T>
    void unregisterEvents() {
        auto iter = events.at(T);
        iter.clear();
    };

    template<EventBase::Type T, typename... Args>
    void dispatchEvent(Args... args) {
        auto list = this->getEvents<T>();

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