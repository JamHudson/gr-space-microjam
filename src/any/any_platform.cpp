#include "any_platform.h"
#include "bn_sprite_items_platform.h"

namespace any {

platform::platform(bn::fixed x, bn::fixed y) :
    _x(x),
    _y(y),
    _sprite(bn::sprite_items::platform.create_sprite(x, y))
{
    _sprite.set_z_order(-1);
    _sprite.set_bg_priority(0);
}

platform::platform() : 
    platform(240, 160) 
{
}

void platform::set_position(bn::fixed x, bn::fixed y) {
    _x = x;
    _y = y;
    _sprite.set_position(x, y);
}

bn::fixed platform::x() const { return _x; }
bn::fixed platform::y() const { return _y; }

}