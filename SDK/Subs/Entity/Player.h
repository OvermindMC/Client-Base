#include "Actor.h"

class Player : public Actor {
private:
    virtual ~Player();
public:
    GameMode* getGameMode();
    std::string getUsername();

    void swing();
    void setSprinting(bool);
    void displayClientMsg(std::string);
};