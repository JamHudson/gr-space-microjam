#ifndef JPB_ENEMY_H
#define JPB_ENEMY_H

#include "jpb/jpb_player.h"

namespace jpb {

class jpb_enemy {

    static constexpr int MIN_X = -bn::display::width() / 2;
    static constexpr int MAX_X = bn::display::width() / 2;

    public:
        jpb_enemy(bn::fixed_point enemy_position, bn::size enemy_size, bn::fixed speed);

        void update();

        bn::sprite_ptr _enemy_sprite;
        bn::rect _enemy_box;
        bn::fixed _enemy_speed;

        private:
            bool moving_right = true;
};

}

#endif