#ifndef KGG_ROCK_H
#define KGG_ROCK_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

namespace kgg {

class rock
{
public:
    rock(bn::fixed x, bn::fixed y);

    void update();

    bool active() const;
    bool collides_with(bn::fixed player_x, bn::fixed player_y) const;

private:
    bn::sprite_ptr _sprite;
    bool _active = true;
};

}

#endif