#include "Killaura.h"

Killaura::Killaura(Category* c) : Module(c) {
    this->setBind('R');

    this->registerEvent<LevelEvent, EventPriority::High>(
        [&](const LevelEvent& ev) {
            static float elapsedTime, tickInterval = (this->ticksDelay / 10.f);

            float deltaTime = ImGui::GetIO().DeltaTime;
            elapsedTime += deltaTime;

            if(!ev.mPlayer || elapsedTime < tickInterval)
                return;
            
            elapsedTime = 0.f;
            
            Player* player = ev.mPlayer;
            Vec3 myPos = player->getPosition();
            GameMode* GM = player->getGameMode();
            uint64_t lRuntimeId = player->getRuntimeId();

            int i = 0;
            MCUtils::forEach(
                [&](Actor* entity, bool& continueLoop) {
                    continueLoop = i < 5;
                    player->swing();
                    GM->attack(entity);
                    ++i;
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