#pragma once

#include "../Manager.h"
#include "Module/Module.h"

class Category {
public:
    Category(Manager* mgr) : mgrPtr(mgr) {
        this->mgrPtr = mgr;
    };
    
    Manager* getMgr() const {
        return this->mgrPtr;
    };

    template<typename M>
    void registerMod() {
        static_assert(std::is_base_of<Module, M>::value, "Template Class type must derive from Module");

        std::string name = M(this).getName();
        
        auto iter = std::find_if(this->modules.begin(), this->modules.end(), [&](const std::unique_ptr<Module>& mod) {
            return mod.get()->getName() == name;
        });
        if(iter == this->modules.end()) {
            this->modules.emplace_back(std::make_unique<M>(this));
        } else {
            Debugger::log("Failed to initialize module " + name + " for " + this->getName());
        };
    };

    std::vector<Module*> getModules() const;
    
    virtual ~Category() = default;
    virtual std::string getName() const = 0;
private:
    Manager* mgrPtr = nullptr;
    std::vector<std::unique_ptr<Module>> modules;
};