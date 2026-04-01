#ifndef KGG_PLAYER_H
#define KGG_PLAYER_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

namespace kgg {

class player
{
public:
    player();

    void update();

    bn::fixed x() const; // getter function to get player's position
    bn::fixed y() const;

private:
    bn::sprite_ptr _sprite;
};

}

#endif