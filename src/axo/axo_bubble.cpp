#include "axo/axo_bubble.h"

#include <bn_keypad.h>

#include "bn_sprite_items_axo_bubble.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

/**
 * player constructor
 * 
 * @param starting_position the location to start the player at
 * @param speed the pixels/frame the player moves at in each dimension
 */
bubble::bubble(bn::fixed starting_x, bn::fixed starting_y, bn::fixed speed, bn::size bubble_size) :
    _sprite(bn::sprite_items::axo_bubble.create_sprite(bn::fixed_point(starting_x, starting_y))),
    _speed(speed),
    _size(bubble_size),
    _hitbox(_sprite, _size)
{}

void bubble::update(){
    // shoots bubbles directly upward
    _sprite.set_y(_sprite.y() - _speed);
}

const hitbox& bubble::get_hitbox() const {
        return _hitbox;
    }
}