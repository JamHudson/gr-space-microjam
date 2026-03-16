#include "jpb/jpb_missile.h"
#include "bn_sprite_items_jpb_missile.h"

namespace jpb {

    jpb_missile::jpb_missile(bn::fixed_point starting_position, bn::fixed speed, bn::size size) :
        _sprite(bn::sprite_items::jpb_missile.create_sprite(starting_position)),
        _speed(speed),
        _size(size),
        _bounding_box(bn::rect(_sprite.x().round_integer(), _sprite.y().round_integer(), _size.width(), _size.height()))
    {}

    void jpb_missile::update() {
        _bounding_box = bn::rect(_sprite.x().round_integer(), _sprite.y().round_integer(), _size.width(), _size.height());
        
        _sprite.set_y(_sprite.y() - _speed);
    }
}