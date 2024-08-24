#include "Category.h"
#include "Module/Module.h"

std::vector<Module*> Category::getModules() const {
    std::vector<Module*> list;

    for(auto& mod : this->modules) {
        list.push_back(mod.get());
    };

    return list;
};