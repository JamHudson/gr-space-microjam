#include "knc/knc_cat.h"
#include "bn_keypad.h"
#include "bn_sprite_items_cat_spaceship.h"

namespace knc {

    cat::cat(bn::fixed_point starting_position, bn::fixed speed) :
    _sprite(bn::sprite_items::cat_spaceship.create_sprite(starting_position)),
    _position(starting_position),
    _speed(speed)
{}
void cat::update() {
    if(bn::keypad::left_held() && _position.x() > MIN_X) {
        _position.set_x(_position.x() - _speed);
    }
    if(bn::keypad::right_held() && _position.x() < MAX_X) {
        _position.set_x(_position.x() + _speed);
    }
    if(bn::keypad::up_held() && _position.y() > MIN_Y) {
        _position.set_y(_position.y() - _speed);
    }
    if(bn::keypad::down_held() && _position.y() < MAX_Y) {
        _position.set_y(_position.y() + _speed);
    }

    _sprite.set_position(_position);
}

bn::fixed_point cat::position() const {
    return _position;
}

void cat::set_speed(bn::fixed speed) {
    _speed = speed;
}

} // namespace knc
