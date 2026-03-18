#include "jpb/jpb_enemy.h"
#include "bn_sprite_items_jpb_alien.h"

namespace jpb {

    jpb_enemy::jpb_enemy(bn::fixed_point starting_position, bn::fixed speed, bn::size size) :
        _enemy_sprite(bn::sprite_items::jpb_alien.create_sprite(starting_position)),
        _enemy_speed(speed),
        _enemy_size(size),
        _enemy_box(create_bounding_box(_enemy_sprite, size))
    {}

    void jpb_enemy::update() {
        if (_moving_right) {
            _enemy_sprite.set_x(_enemy_sprite.x() + _enemy_speed);
            if (_enemy_sprite.x() >= MAX_X - _enemy_speed) {
                _moving_right = false;
            }
        }
        if (!_moving_right) {
            _enemy_sprite.set_x(_enemy_sprite.x() - _enemy_speed);
            if (_enemy_sprite.x() <= MIN_X + _enemy_speed) {
                _moving_right = true;
            }
        }

        _enemy_box = create_bounding_box(_enemy_sprite, _enemy_size);
    }

    bool jpb_enemy::enemy_shot(bn::vector<jpb_missile, 10> missiles) const {
        bool hit = false;
        for (jpb_missile& missile : missiles) {
            if (_enemy_box.intersects(missile._bounding_box)) {
                hit = true;
            }
        }
        return hit;
    }
}