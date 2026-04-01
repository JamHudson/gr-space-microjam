#include "kgg/kgg_player.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_items_sprite.h"

namespace kgg {

player::player()
: _sprite(bn::sprite_items::sprite.create_sprite(0, 50)) //player's position at the bottom
{
}

void player::update()
{
    bn::fixed x = _sprite.x();

    if(bn::keypad::left_held()) //left movement
        x -= 1;

    if(bn::keypad::right_held()) //right movement
        x += 1;


    const bn::fixed min_x = -bn::display::width() / 2 + 8; // left and right limits
    const bn::fixed max_x = bn::display::width() / 2 - 8;

    if(x < min_x)
    {
        x = min_x; // stop the player at the edge
    }

    if(x > max_x)
    {
        x = max_x;
    }

    _sprite.set_x(x);
}

// return actual sprite posiiton
bn::fixed player::x() const
{
    return _sprite.x();
}

bn::fixed player::y() const
{
    return _sprite.y();
}

} //end 