#include "Flight.h"

Flight::Flight(Category* c) : Module(c) {
    this->registerEvent<EventBase::Type::onLevel, EventBase::Priority::Medium>(
        [&]() {
            Player* player = MC::getPlayer();

            if(player; auto* ac = player->ctx.tryGetComponent<AbilitiesComponent>()) {
                ac->setAbility(AbilitiesIndex::FlySpeed, this->flySpeed);
                ac->setAbility(AbilitiesIndex::Flying, true);
                ac->setAbility(AbilitiesIndex::MayFly, true);
            };
        }
    );

    this->registerEvent<EventBase::Type::onDisable, EventBase::Priority::Low>(
        [&]() {
            Player* player = MC::getPlayer();

            if(player; auto* ac = player->ctx.tryGetComponent<AbilitiesComponent>()) {
                ac->setAbility(AbilitiesIndex::FlySpeed, 0.05f);
                ac->setAbility(AbilitiesIndex::Flying, false);
                ac->setAbility(AbilitiesIndex::MayFly, false);
            };
        }
    );
};

std::string Flight::getName() const {
    return "Flight";
};