#include "Hitbox.h"

Hitbox::Hitbox(Category* c) : Module(c) {
    this->registerEvent<EventBase::Type::onLevel, EventBase::Priority::Medium>(
        [&]() {
            Player* player = MC::getPlayer();

            if(!player)
                return;
            
            uint64_t lRuntimeId = player->getRuntimeId();

            MCUtils::forEach(
                [&](Actor* entity, bool& shouldContinue) {
                    uint8_t typeId = entity->getEntityTypeId();

                    if(auto* sc = entity->ctx.tryGetComponent<AABBShapeComponent>()) {
                        if(!this->cached.contains(typeId)) {
                            this->cached.emplace(typeId, sc->mSize);
                        };

                        if(this->cached.contains(typeId)) {
                            sc->mSize = this->tSize;
                        };
                    };
                }, nullptr, [&](Actor* entity) -> bool {
                    uint8_t typeId = entity->getEntityTypeId();

                    return (
                        entity->getRuntimeId() != lRuntimeId && (
                            typeId == 63 || MCUtils::isHostile(typeId) || MCUtils::isPassive(typeId)
                        )
                    );
                }
            );
        }
    );

    this->registerEvent<EventBase::Type::onDisable, EventBase::Priority::Medium>(
        [&]() {
            this->revert();
        }
    );
};

Hitbox::~Hitbox() {
    this->revert();
};

std::string Hitbox::getName() const {
    return "Hitbox";
};

void Hitbox::revert() {
    Player* player = MC::getPlayer();

    if(!player)
        return;
    
    uint64_t lRuntimeId = player->getRuntimeId();
    
    MCUtils::forEach(
        [&](Actor* entity, bool& shouldContinue) {
            uint8_t typeId = entity->getEntityTypeId();

            if(auto* sc = entity->ctx.tryGetComponent<AABBShapeComponent>()) {
                if(this->cached.contains(typeId)) {
                    Vec2 oSize = this->cached.at(typeId);
                    sc->mSize = oSize;
                };
            };
        }, nullptr, [&](Actor* entity) -> bool {
            uint8_t typeId = entity->getEntityTypeId();

            return (
                entity->getRuntimeId() != lRuntimeId && (
                    typeId == 63 || MCUtils::isHostile(typeId) || MCUtils::isPassive(typeId)
                )
            );
        }
    );
};