#include "AutoSprint.h"

AutoSprint::AutoSprint(Category* c) : Module(c) {
    this->registerEvent<EventBase::Type::onLevel, EventBase::Priority::Low>(
        [&]() {
            Player* player = MC::getPlayer();

            if(player) {
                if(player->isMoving()) {
                    player->setSprinting(true);
                };
            };
        }
    );
};

std::string AutoSprint::getName() const {
    return "AutoSprint";
};