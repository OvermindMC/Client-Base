#pragma once

#include "Subs/LerpEvent.h"
#include "Subs/LevelEvent.h"
#include "Subs/RenderEvent.h"
#include "Subs/KeyInputEvent.h"
#include "Subs/MouseInputEvent.h"

class EventBase {
public:
    virtual ~EventBase() = default;
    virtual const std::type_info& getType() const = 0;
};

template<typename T>
class Event : public EventBase {
public:
    using CallbackType = std::function<void(const T&)>;

    Event(CallbackType event_callback) : callback_(event_callback) {}

    const std::type_info& getType() const override {
        return typeid(T);
    };

    void call(const T& event) {
        callback_(event);
    };
private:
    CallbackType callback_;
};