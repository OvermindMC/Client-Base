#include "Flight.h"

Flight::Flight(Category* c) : Module(c) {
    this->registerEvent<LevelEvent, EventPriority::Medium>(
        [&](const LevelEvent& ev) {
            if(ev.mPlayer) {
                if(auto* ac = ev.mPlayer->ctx.tryGetComponent<AbilitiesComponent>()) {
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
                };
            } else {
                if(this->canModify)
                    this->canModify = false;
                
                this->setIsEnabled(false);
            };
        }
    );

    this->registerEvent<ModuleEvent, EventPriority::Low>(
        [&](const ModuleEvent& ev) {
            if(!ev.isEnabled) {
                this->revert();
            };
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

    if(!player || !this->canModify) {
        this->canModify = false;
        return;
    };

    if(auto* ac = player->ctx.tryGetComponent<AbilitiesComponent>()) {
        ac->setAbility(AbilitiesIndex::FlySpeed, 0.05f);
        ac->setAbility(AbilitiesIndex::MayFly, this->prevStates.first);
        ac->setAbility(AbilitiesIndex::Flying, this->prevStates.second);
    };

    this->canModify = false;
};