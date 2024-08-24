#include "Category.h"
#include "Module/Module.h"

void Category::registerMod(std::unique_ptr<Module> mod) {
    this->modules.emplace_back(std::move(mod));
};

std::vector<Module*> Category::getModules() const {
    std::vector<Module*> list;

    for(auto& mod : this->modules) {
        list.push_back(mod.get());
    };

    return list;
};