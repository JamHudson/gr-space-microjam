#include "bal/bal_player.h"

#include <bn_keypad.h>

#include "bn_sprite_items_bal_dot.h"

namespace bal {

    player::player(bn::fixed_point starting_position, bn::fixed speed) :
    _sprite(bn::sprite_items::bal_dot.create_sprite(starting_position)),
    _speed(speed),
    bounding_box(bn::rect(starting_position.x().round_integer(), starting_position.y().round_integer(), 8, 8))
    {}

    void player::update() {
    if(bn::keypad::left_held() && !(_sprite.x() < MIN_X)) {
        _sprite.set_x(_sprite.x() - _speed);
    }
    if(bn::keypad::right_held() && !(_sprite.x() > MAX_X)) {
        _sprite.set_x(_sprite.x() + _speed);
    }
    if(bn::keypad::up_held() && !(_sprite.y() < MIN_Y)) {
        _sprite.set_y(_sprite.y() - _speed);
    }
    if(bn::keypad::down_held() && !(_sprite.y() > MAX_Y)) {
        _sprite.set_y(_sprite.y() + _speed);
    }
    bounding_box = bn::rect(_sprite.x().round_integer(), _sprite.y().round_integer(), 8, 8);
}

}