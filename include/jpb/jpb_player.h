#ifndef JPB_PLAYER_H
#define JPB_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_size.h>
#include "jpb/jpb_enemy.h"
#include "jpb/jpb_missile.h"
#include <bn_vector.h>

namespace jpb {

bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

class jpb_player {

    static constexpr int MIN_X = -bn::display::width() / 2;
    static constexpr int MAX_X = bn::display::width() / 2;
    
    public:
        jpb_player(bn::fixed_point player_position, bn::size player_size, bn::fixed _speed);

        void update();

        bool enemy_shot(bn::rect missile_box, bn::rect enemy_box) const;

        void shoot(bn::vector<jpb_missile, 10>& _missiles);
    
        bn::sprite_ptr _player_sprite;
        bn::fixed _speed;
        bn::rect _player_box;
};

}

#endif