#ifndef JPB_ENEMY_H
#define JPB_ENEMY_H

#include "jpb/jpb_player.h"
#include "jpb/jpb_missile.h"

namespace jpb {

class jpb_enemy {

    public:
        jpb_enemy(bn::fixed_point enemy_position, bn::fixed speed, bn::size enemy_size);

        void update();

        bool enemy_shot(bn::vector<jpb_missile, 10> missiles) const;

        bn::sprite_ptr _enemy_sprite;
        bn::fixed _enemy_speed;
        bn::size _enemy_size;
        bn::rect _enemy_box;

        private:
            bool _moving_right = true;
};

}

#endif