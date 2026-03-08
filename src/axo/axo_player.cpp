#include <bn_keypad.h>

#include "axo/axo_player.h"
#include "bn_sprite_items_axo_axolotl.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
static bn::rect create_bounding_box(bn::sprite_ptr _sprite, bn::size box_size)
{
    return bn::rect(_sprite.x().round_integer(),
                    _sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

/**
 * player constructor
 * 
 * @param starting_position the location to start the player at
 * @param speed the pixels/frame the player moves at in each dimension
 */
player::player(bn::fixed_point starting_position, bn::fixed speed, bn::size player_size) :
    _sprite(bn::sprite_items::axo_axolotl.create_sprite(starting_position)),
    _speed(speed)
    _size(player_size)
    {}

/**
 * Reads from the d-pad and moves the player by one frame accordingly.
 */
void player::update() {
    if(bn::keypad::left_held()) {
        _sprite.set_x(_sprite.x() - _speed);
    }
    if(bn::keypad::right_held()) {
        _sprite.set_x(_sprite.x() + _speed);
    }
    if(bn::keypad::up_held()) {
        _sprite.set_y(_sprite.y() - _speed);
    }
    if(bn::keypad::down_held()) {
        _sprite.set_y(_sprite.y() + _speed);
    }

    // Keeps player from escaping the screen.
    if (_sprite.x() < MIN_X) {
        _sprite.set_x(MIN_X);
    }
    if (_sprite.x() > MAX_X) {
        _sprite.set_x(MAX_X);
    }
    if (_sprite.y() < MIN_Y) {
        _sprite.set_y(MIN_Y);   
    }
    if (_sprite.y() > MAX_Y) {
        _sprite.set_y(MAX_Y);
    }
}

bool player::still_alive() const {
    // We'll define this later.
    // return _alive;
}

}