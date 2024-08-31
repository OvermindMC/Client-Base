#pragma once

#include "../Category.h"

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

    template<EventBase::Type T>
    std::vector<EventBase*> getEvents() const {
        return this->evH->getEvents<T>();
    };

    template<EventBase::Type T, EventBase::Priority P, typename... Args>
    void registerEvent(std::function<typename std::conditional<sizeof...(Args) == 0, void(), void(Args...)>::type >callback) {
        this->evH->registerEvent<T, P, Args...>(callback);
    };

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