#pragma once

#include "../Category.h"

struct ModuleEvent { bool isEnabled; }; struct ModuleTickEvent : ModuleEvent {};

class Module {
public:
    Module(Category*);

    Category* getCategory() const;
    Manager* getMgr() const;

    virtual ~Module() = default;
    virtual std::string getName() const = 0;

    void baseTick();

    void setIsEnabled(bool);
    void toggleIsEnabled();
    bool isEnabled() const;
    bool wasEnabled() const;

    void setBind(uint64_t);
    uint64_t getBind();

    template<typename T>
    auto getEvents() const {
        return this->evH->getEvents<T>();
    };

    template<typename T, EventPriority P>
    void registerEvent(std::function<void(const T&)> callback) {
        this->evH->registerEvent<T, P>(callback);
    };

    /*template<EventType T, EventPriority P, typename... Args>
    void registerEvent(std::function<typename std::conditional<sizeof...(Args) == 0, void(), void(Args...)>::type >callback) {
        this->evH->registerEvent<T, P, Args...>(callback);
    };*/

    bool needsEvents(char state = -1) {
        if(state != -1) {
            this->obtainAllEvents = state;
        };
        return this->obtainAllEvents;
    };
private:
    Category* cPtr = nullptr;
    uint64_t modBindKey = NULL;
    bool obtainAllEvents = false;
    std::unique_ptr<EventHandler> evH;
    std::pair<bool, bool> state = { 0, 0 };
};