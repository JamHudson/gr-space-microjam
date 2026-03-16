#ifndef KGG_PLAYER_H
#define KGG_PLAYER_H

#include "bn_sprite_ptr.h"

namespace kgg {

class player
{
public:
    player();

    void update();

private:
    bn::sprite_ptr _sprite;
};

}

#endif