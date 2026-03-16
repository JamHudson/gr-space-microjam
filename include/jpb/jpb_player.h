#ifndef JPB_PLAYER_H
#define JPB_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_fixed.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_vector.h>

#include "jpb/jpb_enemy.h"
#include "jpb/jpb_missile.h"

namespace jpb {

static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

bn::rect create_bounding_box(bn::sprite_ptr& sprite, bn::size& box_size);

class jpb_player {
    
    public:
        jpb_player(bn::fixed_point player_position, bn::fixed speed, bn::size size);

        void update();

        void shoot(bn::vector<jpb_missile, 10>& _missiles);
    
        private:
            bn::sprite_ptr _player_sprite;
            bn::fixed _speed;
            bn::size _player_size;
            bn::rect _player_box;
};

}

#endif