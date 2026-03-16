#include "kgg/kgg_player.h"

#include "bn_keypad.h"
#include "bn_sprite_items_sprite.h"

namespace kgg {

player::player()
: _sprite(bn::sprite_items::sprite.create_sprite(0, 0))
{
}

void player::update()
{
    bn::fixed x = _sprite.x();
    bn::fixed y = _sprite.y();

    if(bn::keypad::left_held())
        x -= 1;

    if(bn::keypad::right_held())
        x += 1;

    if(bn::keypad::up_held())
        y -= 1;

    if(bn::keypad::down_held())
        y += 1;

    _sprite.set_position(x, y);
}

}