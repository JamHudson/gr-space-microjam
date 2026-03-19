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
    _hitbox(_sprite, bn::size(14, 20), bn::fixed_point(0, -4))
    // The player sprite has negative space around its tail, so I shrank the hitbox and slid it up.
    // Better for close calls!
{
}

/**
 * Reads from the d-pad and moves the player by one frame accordingly.
 */
void player::update() {
    // TODO: Determine frame rate of animation. 5 feels too fast, but it will work for right now.
    if(bn::keypad::left_held()) {
        _sprite.set_x(_sprite.x() - _speed);
        if(!_is_animating) {
            _is_animating = true;
            _sprite.set_horizontal_flip(false);
            _sprite_action = bn::create_sprite_animate_action_forever(_sprite, 5, 
                bn::sprite_items::axo_axolotl.tiles_item(), 5, 6);
        }
    }
    else if(bn::keypad::right_held()) {
        _sprite.set_x(_sprite.x() + _speed);
        if(!_is_animating) {
            _is_animating = true;
            _sprite.set_horizontal_flip(true);
            _sprite_action = bn::create_sprite_animate_action_forever(_sprite, 5, 
                bn::sprite_items::axo_axolotl.tiles_item(), 5, 6);
        }
    }
    else if(bn::keypad::up_held()) {
        _sprite.set_y(_sprite.y() - _speed);
        if(!_is_animating) {
            _is_animating = true;
            _sprite.set_horizontal_flip(false);
            _sprite_action = bn::create_sprite_animate_action_forever(_sprite, 5, 
                bn::sprite_items::axo_axolotl.tiles_item(), 1, 2);
        }
    }
    else if(bn::keypad::down_held()) {
        _sprite.set_y(_sprite.y() + _speed);
        if(!_is_animating) {
            _is_animating = true;
            _sprite.set_horizontal_flip(false);
            _sprite_action = bn::create_sprite_animate_action_forever(_sprite, 5, 
                bn::sprite_items::axo_axolotl.tiles_item(), 3, 4);
        }
    }
    else {
        _sprite_action.reset();
        _is_animating = false;
        _sprite.set_horizontal_flip(false);
        _sprite.set_tiles(bn::sprite_items::axo_axolotl.tiles_item().create_tiles(0));
    }

    if(_sprite_action) {
        _sprite_action->update();
    }

    if(bn::keypad::a_pressed() || bn::keypad::b_pressed()) {
        if(bubbles.size() < bubbles.max_size()) {
            bubbles.push_back(bubble(_sprite.x(), _sprite.y() - 5, BUBBLE_SPEED, 
            BUBBLE_SIZE));
        bn::sound_items::axo_pop.play(); // play bubble sound
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

    void player::destroy_bubble(int index) {
        bubbles.erase(bubbles.begin() + index);
    }

    void player::clear_bubbles() {
        bubbles.clear();
    }
}