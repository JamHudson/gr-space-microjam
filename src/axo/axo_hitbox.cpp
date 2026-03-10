#include "axo/axo_hitbox.h"

namespace axo {

hitbox::hitbox(const bn::sprite_ptr& sprite, bn::size size) :
    _sprite(sprite),
    _size(size)
{}

bn::rect hitbox::rect() const {
    return bn::rect(
        bn::point(_sprite.x().right_shift_integer(), _sprite.y().right_shift_integer()),
        _size
    );
}

bool hitbox::intersects(const hitbox& other) const {
    return rect().intersects(other.rect());
}
}