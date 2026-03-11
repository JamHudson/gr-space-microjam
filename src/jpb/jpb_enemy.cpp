#include "jpb/jpb_enemy.h"
#include "bn_sprite_items_jpb_alien.h"
#include "jpb_missile.h"

namespace jpb {

    jpb_enemy::jpb_enemy(bn::fixed_point starting_position, bn::size size, bn::fixed speed) :
        _enemy_sprite(bn::sprite_items::jpb_alien.create_sprite(starting_position)),
        _enemy_box(create_bounding_box(_enemy_sprite, size)),
        _enemy_speed(speed)
    {}

    void jpb_enemy::update() {
        if (moving_right) {
            _enemy_sprite.set_x(_enemy_sprite.x() + _enemy_speed);
            if (_enemy_sprite.x() == MAX_X - _enemy_speed) {
                moving_right = false;
            }
        }
        if (!moving_right) {
            _enemy_sprite.set_x(_enemy_sprite.x() - _enemy_speed);
            if (_enemy_sprite.x() == MIN_X + _enemy_speed) {
                moving_right = true;
            }
        }

        _enemy_box = create_bounding_box(_enemy_sprite, {8, 8});
    }
}