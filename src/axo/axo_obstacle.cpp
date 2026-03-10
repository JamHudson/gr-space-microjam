#include "axo/axo_obstacle.h"

#include <bn_keypad.h>

#include "bn_sprite_items_axo_obstacle.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

/**
 * player constructor
 * 
 * @param starting_position the location to start the player at
 * @param speed the pixels/frame the player moves at in each dimension
 */
obstacle::obstacle(bn::fixed starting_x, bn::fixed starting_y, bn::fixed speed, bn::size obstacle_size) :
    _sprite(bn::sprite_items::axo_obstacle.create_sprite(bn::fixed_point(starting_x, starting_y))),
    _speed(speed),
    _size(obstacle_size),
    _hitbox(_sprite, _size)
{}

void obstacle::update(player& player){
    // moves obstacles towards the right
    _sprite.set_x(_sprite.x() + _speed);
}

const hitbox& obstacle::get_hitbox() const {
        return _hitbox;
    }
}