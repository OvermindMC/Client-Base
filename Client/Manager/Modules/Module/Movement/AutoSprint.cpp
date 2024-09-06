#include "AutoSprint.h"

AutoSprint::AutoSprint(Category* c) : Module(c) {
    this->registerEvent<LevelEvent, EventPriority::Low>(
        [&](const LevelEvent& ev) {
            if(ev.mPlayer && ev.mPlayer->isMoving()) {
                ev.mPlayer->setSprinting(true);
            };
        }
    );
};

std::string AutoSprint::getName() const {
    return "AutoSprint";
};