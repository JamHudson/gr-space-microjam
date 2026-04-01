#ifndef KGG_ROCK_H
#define KGG_ROCK_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

namespace kgg {

class rock
{
public:
    rock(bn::fixed x, bn::fixed y, bn::fixed speed);

    void update();

    bool active() const;
    bool collides_with(bn::fixed player_x, bn::fixed player_y) const;

private:
    bn::sprite_ptr _sprite;
    bn::fixed _speed; // speed
    bool _active = true;

    bn::sprite_animate_action<2> _animation;
};

}

#endif