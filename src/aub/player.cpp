#include "aub/player.h"

#include <bn_keypad.h>

#include "bn_sprite_items_aub_triangle.h"

#include "bn_sound_items.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace aub {

/**
 * player constructor
 * 
 * @param starting_position the location to start the player at
 * @param speed the pixels/frame the player moves at in each dimension
 */
player::player(bn::fixed_point starting_position, bn::fixed speed) :
    _sprite(bn::sprite_items::aub_triangle.create_sprite(starting_position)),
    _sprite_action(bn::create_sprite_animate_action_forever(_sprite, 16, bn::sprite_items::aub_triangle.tiles_item(), 0, 1, 2, 3)),
    _speed(speed)
    {}


void player::update() {
    _update_position();
    _update_animation();
}

/**
 * Reads from the d-pad and moves the player by one frame accordingly.
 */
void aub::player::_update_position() {
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
}

/**
 * Reads from the d-pad and sets direction sprites is pointing.
 * Regardless of direction, updates the sprite animation action.
 */
void aub::player::_update_animation() {
    if(bn::keypad::left_pressed()) {
       _sprite_action = bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::aub_triangle.tiles_item(), 8, 9, 10, 11);
    }
    if(bn::keypad::right_pressed()) {
        _sprite_action = bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::aub_triangle.tiles_item(), 0, 1, 2, 3);
    }
    if(bn::keypad::up_pressed()) {
        _sprite_action = bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::aub_triangle.tiles_item(), 4, 5, 6, 7);
    }
    if(bn::keypad::down_pressed()) {
       _sprite_action = bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::aub_triangle.tiles_item(), 12, 13, 14, 15);
    }

    if(bn::keypad::any_pressed()) {
        bn::sound_items::aub_beep.play();
    }
    _sprite_action.update();
}

/**
 * Returns whether the player has left the screen
 * 
 * @return true if the player has left the screen, false if it is still on the screen
 */
bool player::out_of_bounds() const {
    return _sprite.x() > MAX_X ||
           _sprite.x() < MIN_X ||
           _sprite.y() > MAX_Y ||
           _sprite.y() < MIN_Y;
}
}