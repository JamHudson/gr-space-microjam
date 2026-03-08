#include "axo/axo_obstacle.h"

#include <bn_keypad.h>

#include "bn_sprite_items_axo_obstacle.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace axo {
    static bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size)
    {
           return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
    }

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
    _bounding_box(create_bounding_box(_sprite, _size))
{}

void obstacle::update(player& player){
    _bounding_box = create_bounding_box(_sprite, _size);
}
}