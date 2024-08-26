#pragma once

#include "../Category.h"

class Module {
public:
    Module(Category* c) : evH(std::make_unique<EventHandler>(this)) {
        this->cPtr = c;
    };

    Category* getCategory() const;
    Manager* getMgr() const;

    virtual ~Module() = default;
    virtual std::string getName() const = 0;

    void baseTick();
    bool isEnabled() const;
    void setIsEnabled(bool);
    
    virtual void onTick() {};
    virtual void onEnable() {};
    virtual void onDisable() {};
    
    virtual void onImRender() {};
    virtual void onLevel(void*) {};
private:
    Category* cPtr = nullptr;
    std::unique_ptr<EventHandler> evH;
    std::pair<bool, bool> state = { 0, 0 };
};