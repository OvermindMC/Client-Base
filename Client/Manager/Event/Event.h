#pragma once

#include "../../../Mem/Mem.h"
#include "../../../Utils/Utils.h"

class EventBase {
public:
    enum class Type {
        onTick = 1, onEnable = 2, onDisable = 3, onLerp = 4, onLevel = 5, onRender = 6
    };

    enum class Priority {
        Low = 1, Medium = 2, High = 3
    };

    virtual ~EventBase() = default;

    virtual Type getType() const = 0;
    virtual Priority getPriority() const = 0;
};

template<EventBase::Type T, EventBase::Priority P, typename... Args>
class Event : public EventBase {
public:
    Event(std::function<void(Args...)> event_callback) : callback(event_callback) {};

    EventBase::Type getType() const override {
        return T;
    };
    EventBase::Priority getPriority() const override {
        return P;
    };

    void call(Args... args) {
        if(this->callback) {
            this->callback(args...);
        };
    };
private:
    std::function<void(Args...)> callback;
};