#include "cat/cat_player.h"

#include <bn_keypad.h>

#include "bn_sprite_items_cat_player.h"

namespace cat {

cat_player::cat_player(bn::fixed_point starting_position, bn::fixed speed) :
    _sprite(bn::sprite_items::cat_player.create_sprite(starting_position)),
    _speed(speed)
    {}

void cat_player::update() {
    if(bn::keypad::left_held())  _sprite.set_x(_sprite.x() - _speed);
    if(bn::keypad::right_held()) _sprite.set_x(_sprite.x() + _speed);
    if(bn::keypad::up_held())    _sprite.set_y(_sprite.y() - _speed);
    if(bn::keypad::down_held())  _sprite.set_y(_sprite.y() + _speed);

    // clamp to screen bounds
    if(_sprite.x() > MAX_X) _sprite.set_x(MAX_X);
    if(_sprite.x() < MIN_X) _sprite.set_x(MIN_X);
    if(_sprite.y() > MAX_Y) _sprite.set_y(MAX_Y);
    if(_sprite.y() < MIN_Y) _sprite.set_y(MIN_Y);
}

bn::fixed_point cat_player::position() const {
    return { _sprite.x(), _sprite.y() };
}

}