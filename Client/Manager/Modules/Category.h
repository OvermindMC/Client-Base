#pragma once

#include "../Manager.h"

class Category {
public:
    Category(Manager* mgr) : mgrPtr(mgr) {
        this->mgrPtr = mgr;
    };
    
    Manager* getMgr() const {
        return this->mgrPtr;
    };

    void registerMod(std::unique_ptr<Module> mod);
    std::vector<Module*> getModules() const;
    
    virtual ~Category() = default;
    virtual std::string getName() const = 0;
private:
    Manager* mgrPtr = nullptr;
    std::vector<std::unique_ptr<Module>> modules;
};