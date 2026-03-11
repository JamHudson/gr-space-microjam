#include "jpb/jpb_player.h"
#include <bn_keypad.h>
#include "bn_sprite_items_jpb_ship.h"
#include "bn_sprite_items_jpb_missile.h"
#include "bn_vector.h"

namespace jpb {
    
    bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size) {
        return bn::rect(sprite.x().round_integer(),
                        sprite.y().round_integer(),
                        box_size.width(),
                        box_size.height());
    }

    jpb_player::jpb_player(bn::fixed_point starting_position, bn::size size, bn::fixed speed) :
        _player_sprite(bn::sprite_items::jpb_ship.create_sprite(starting_position)),
        _speed(speed),
        _player_box(create_bounding_box(_player_sprite, size))
    {}
    
    void jpb_player::update() {
        if(bn::keypad::left_held()) {
            _player_sprite.set_x(_player_sprite.x() - _speed);
        }
        if(bn::keypad::right_held()) {
            _player_sprite.set_x(_player_sprite.x() + _speed);
        }

        _player_box = create_bounding_box(_player_sprite, {16, 8});

    }

    bool jpb_player::enemy_shot(bn::rect missile_box, bn::rect enemy_box) const {
        return missile_box.intersects(enemy_box);
    }

    void jpb_player::shoot(bn::vector<jpb_missile, 10>& _missiles) {
        if (bn::keypad::a_pressed()) {
            if (_missiles.size() < 10 ) {
                _missiles.push_back(jpb_missile({_player_sprite.x(), _player_sprite.y()}, 1, {8, 8}));
            }
        }
    }
}