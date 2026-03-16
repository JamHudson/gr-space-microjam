#ifndef BAL_PLAYER_H
#define BAL_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_size.h>

#include "bal_screen_size.h"

namespace bal
{
class player{

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // The pixels/frame the player moves in each dimension
        bn::fixed _speed;

    public:
        player(bn::fixed_point starting_position, bn::fixed speed);
        void update();

        bn::rect bounding_box;

    
};

}

#endif