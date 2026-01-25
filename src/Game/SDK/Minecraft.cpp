#include "Minecraft.h"

#include "Entity/Context/Components/LevelComponent.h"
#include "Entity/Context/Components/ActorOwnerComponent.h"

Level* Minecraft::getLevel() {
    if(auto ctx = getEntContext()) {
        if(auto c = ctx->tryGetComponent<LevelComponent>()) {
            return c->mLevel;
        };
    };
    return nullptr;
};

std::vector<Actor*> Minecraft::getEntities() {
    std::vector<Actor*> result;
    
    if(auto ctx = getEntContext()) {
        auto& registry = ctx->enttRegistry;

        for(auto ent : registry.view<ActorOwnerComponent>()) {
            if(!registry.valid(ent))
                continue;
            
            if(auto c = registry.try_get<ActorOwnerComponent>(ent)) {
                result.push_back(c->mActor);
            };
        };
    };

    return result;
};