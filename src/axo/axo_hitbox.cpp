#include "axo/axo_hitbox.h"

namespace axo {

hitbox::hitbox(const bn::sprite_ptr& sprite, bn::size size, bn::fixed_point offset) :
    _sprite(sprite),
    _size(size),
    _offset(offset)
{
}

bn::rect hitbox::rect() const {
    return bn::rect(
        bn::point((_sprite.x() + _offset.x()).right_shift_integer(), (_sprite.y() + 
            _offset.y()).right_shift_integer()),
        _size
    );
}

bool hitbox::intersects(const hitbox& other) const {
    return rect().intersects(other.rect());
}
}