#include "Category.h"
#include "Module/Module.h"

Category::Category(ClientContext* ctx, std::string name) noexcept : ctxPtr(ctx), mName(std::move(name)) {
    //
};

Category::~Category() noexcept {
    mModules.clear();
};

ClientContext* Category::getContext() const noexcept {
    return ctxPtr;
};

const std::string& Category::getName() const noexcept {
    return mName;
};

void Category::addModule(std::unique_ptr<Module> mod) noexcept {
    if(!mod)
        return;
    
    auto iter = std::find_if(
        mModules.begin(), mModules.end(), [&](auto& ptr) {
            return ptr->getName() == mod->getName();
        }
    );

    if(iter == mModules.end()) {
        mModules.emplace_back(std::move(mod));
    };
};

const std::vector<std::unique_ptr<Module>>& Category::getModules() const noexcept {
    return mModules;
};