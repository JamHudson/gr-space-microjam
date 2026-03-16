#include "jpb/jpb_player.h"
#include <bn_keypad.h>
#include "bn_sprite_items_jpb_ship.h"

namespace jpb {
    jpb_player::jpb_player(bn::fixed_point starting_position, bn::fixed_point enemy_position, bn::fixed speed) :
        _player_sprite(bn::sprite_items::jpb_ship.create_sprite(starting_position)),
        _enemy_sprite(bn::sprite_items::jpb_ship.create_sprite(enemy_position)),
        _speed(speed)
    {}

    void jpb_player::update() {
        if(bn::keypad::left_held()) {
            _player_sprite.set_x(_player_sprite.x() - _speed);
        }
        if(bn::keypad::right_held()) {
            _player_sprite.set_x(_player_sprite.x() + _speed);
        }
        if(bn::keypad::up_held()) {
            _player_sprite.set_y(_player_sprite.y() - _speed);
        }
        if(bn::keypad::down_held()) {
            _player_sprite.set_y(_player_sprite.y() + _speed);
        }
    }

    // We'll improve this to have bounding boxes next wave
    bool jpb_player::enemy_intersect() const {
        return _player_sprite.x() == _enemy_sprite.x() && _player_sprite.y() == _enemy_sprite.y();
    }
}