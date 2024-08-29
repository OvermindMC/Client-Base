#include "Minecraft.h"

ClientInstance* MC::getClientInstance() {
    static uintptr_t ref = (uintptr_t)Mem::getRef("E8 ? ? ? ? 90 0F 57 C0 0F 11 45 68 66 0F 6F 0D ? ? ? ?", 0x2C);
    
    static int relOff = *(int*)(ref + 3);
    static uintptr_t baseOffset = (uintptr_t)(uintptr_t**)(ref + relOff + 7);

    static auto ptr = Mem::resPtr(baseOffset, { 0x0, 0x58, 0x0, 0x0 });
    return ptr ? (ClientInstance*)ptr : nullptr;
};

Player* MC::getPlayer() {
    ClientInstance* ci = MC::getClientInstance();
    return ci ? ci->getPlayer() : nullptr;
};

std::vector<Actor*> MC::getEntities() {
    std::vector<Actor*> results;

    if (auto player = getPlayer()) {
        auto& ctx = player->ctx;
        auto& registry = ctx.enttRegistry;

        for (auto ent : registry.view<ActorOwnerComponent>()) {
            if (auto* aoc = registry.try_get<ActorOwnerComponent>(ent)) {
                results.push_back(aoc->mActor);
            };
        };
    };

    return results;
};

// MC Utils

bool MCUtils::isHostile(uint8_t typeId) {
    switch(typeId) {
        case 32: case 33: case 34: case 35: case 36: case 37: case 38: case 39: 
        case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47:
        case 48: case 49: case 50: case 52: case 53: case 54: case 55: case 57: 
        case 58: case 59: case 104: case 105: case 110: case 114: case 116: case 123: 
        case 124: case 126: case 127: case 131:
            return true;
        default:
            return false;
    };
};

bool MCUtils::isPassive(uint8_t typeId) {
    switch(typeId) {
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: 
        case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 25:
        case 26: case 27: case 28: case 29: case 30: case 31: case 74: case 75: 
        case 108: case 109: case 111: case 112: case 113: case 115: case 118: 
        case 121: case 122: case 125: case 128: case 132: case 133: case 134:
            return true;
        default:
            return false;
    };
};

void MCUtils::forEach(std::function<void(Actor*, bool&)> callback, std::function<bool(Actor*, Actor*)> sort, std::function<bool(Actor*)> includeOnly) {
    std::vector<Actor*> entities = MC::getEntities();
    bool continueLoop = true;

    if(entities.empty())
        return;
    
    if(sort) {
        std::sort(entities.begin(), entities.end(), sort);
    };

    entities.erase(std::remove_if(entities.begin(), entities.end(), [](Actor* ent) {
        return ent == nullptr || !ent->isAlive();
    }), entities.end());

    if (includeOnly) {
        entities.erase(std::remove_if(entities.begin(), entities.end(), [&](Actor* ent) {
            return !includeOnly(ent);
        }), entities.end());
    };

    for(auto ent : entities) {
        callback(ent, continueLoop);
        
        if(!continueLoop)
            break;
    };
};