#include "Flight.h"

Flight::Flight(Category* c) : Module(c) {
    this->registerEvent<EventBase::Type::onRender, EventBase::Priority::Medium>(
        [&]() {
            Player* player = MC::getPlayer();

            if(player; auto* ac = player->ctx.tryGetComponent<AbilitiesComponent>()) {
                if(!this->canModify) {
                    this->prevStates = {
                        *ac->getAbility<bool>(AbilitiesIndex::MayFly),
                        *ac->getAbility<bool>(AbilitiesIndex::Flying)
                    };
                    this->canModify = true;
                };
                
                if(this->canModify) {
                    ac->setAbility(AbilitiesIndex::FlySpeed, this->flySpeed);
                    ac->setAbility(AbilitiesIndex::Flying, true);
                    ac->setAbility(AbilitiesIndex::MayFly, true);
                };
            } else {
                if(this->canModify)
                    this->canModify = false;
                
                this->setIsEnabled(false);
            };
        }
    );

    this->registerEvent<EventBase::Type::onDisable, EventBase::Priority::Low>(
        [&]() {
            this->revert();
        }
    );
};

Flight::~Flight() {
    this->revert();
};

std::string Flight::getName() const {
    return "Flight";
};

void Flight::revert() {
    Player* player = MC::getPlayer();

    if(!player || !this->canModify)
        return;

    if(auto* ac = player->ctx.tryGetComponent<AbilitiesComponent>()) {
        ac->setAbility(AbilitiesIndex::FlySpeed, 0.05f);
        ac->setAbility(AbilitiesIndex::MayFly, this->prevStates.first);
        ac->setAbility(AbilitiesIndex::Flying, this->prevStates.second);
    };

    this->canModify = false;
};