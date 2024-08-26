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
    bool isEnabled() const;
    bool wasEnabled() const;

    template<EventBase::Type T>
    std::vector<EventBase*> getEvents() const {
        return this->evH->getEvents<T>();
    };

    template<EventBase::Type T, EventBase::Priority P, typename... Args>
    void registerEvent(std::function<typename std::conditional<sizeof...(Args) == 0, void(), void(Args...)>::type >callback) {
        this->evH->registerEvent<T, P, Args...>(callback);
    };
private:
    Category* cPtr = nullptr;
    std::unique_ptr<EventHandler> evH;
    std::pair<bool, bool> state = { 0, 0 };
};