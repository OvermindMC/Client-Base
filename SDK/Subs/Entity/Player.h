#include "Actor.h"

class Player : public Actor {
private:
    virtual ~Player();
public:
    void setSprinting(bool);
};