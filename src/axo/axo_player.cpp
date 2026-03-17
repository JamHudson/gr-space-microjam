#include <bn_keypad.h>
#include <bn_vector.h>

#include "axo/axo_player.h"
#include "axo/axo_obstacle.h"
#include "axo/axo_bubble.h"
#include "bn_sprite_items_axo_axolotl.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

/**
 * player constructor
 * 
 * @param starting_position the location to start the player at
 * @param speed the pixels/frame the player moves at in each dimension
 */
player::player(bn::fixed_point starting_position, bn::fixed speed, bn::size player_size) :
    _sprite(bn::sprite_items::axo_axolotl.create_sprite(starting_position)),
    _speed(speed),
    _size(player_size),
    _hitbox(_sprite, _size)
{
}

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

    if(bn::keypad::a_pressed() || bn::keypad::b_pressed()) {
        if(bubbles.size() < bubbles.max_size()) {
            bubbles.push_back(bubble(_sprite.x(), _sprite.y(), BUBBLE_SPEED, 
            BUBBLE_SIZE));
        }
    }

    for(int i = 0; i < bubbles.size(); ) {
        bubbles[i].update();

        if(bubbles[i].y() < MIN_Y) {
            bubbles[i] = bubbles.back();
            bubbles.pop_back();
        }

        else {
            ++i;
        }
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

    const hitbox& player::get_hitbox() const {
        return _hitbox;
    }

    bool player::alive() const {
        return _alive;
    }

    void player::kill() {
        _alive = false;
    }

    void player::clear_bubbles() {
        bubbles.clear();
    }
}