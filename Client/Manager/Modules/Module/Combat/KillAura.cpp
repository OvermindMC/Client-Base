#include "Killaura.h"

Killaura::Killaura(Category* c) : Module(c) {
    this->setBind('R');

    this->registerEvent<EventBase::Type::onLevel, EventBase::Priority::High>(
        [&]() {
            Player* player = MC::getPlayer();
            Vec3 myPos = player->getPosition();
            GameMode* GM = player->getGameMode();
            uint64_t lRuntimeId = player->getRuntimeId();

            MCUtils::forEach(
                [&](Actor* entity, bool& continueLoop) {
                    player->swing();
                    GM->attack(entity);
                    continueLoop = false;
                }, [&](Actor* a, Actor* b) -> bool {
                    return a->getPosition().dist(myPos) < b->getPosition().dist(myPos);
                }, [&](Actor* entity) -> bool {
                    uint8_t typeId = entity->getEntityTypeId();

                    return (
                        entity->getRuntimeId() != lRuntimeId && (
                            typeId == 63 || MCUtils::isHostile(typeId) || MCUtils::isPassive(typeId)
                        ) && entity->getPosition().dist(myPos) < this->range
                    );
                }
            );
        }
    );
};

std::string Killaura::getName() const {
    return "Killaura";
};