#ifndef JPB_PLAYER_H
#define JPB_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_size.h>

namespace jpb {

class jpb_player {
    public:
        jpb_player(bn::fixed_point player_position, bn::fixed_point enemy_position, bn::fixed _speed);

        void update();

        bool enemy_intersect() const;
    
    private:
        bn::sprite_ptr _player_sprite;
        bn::sprite_ptr _enemy_sprite;
        bn::fixed _speed;
};

}

#endif