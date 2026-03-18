#ifndef MAR_ENEMY_H
#define MAR_ENEMY_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>

#include "mar/mar_bounds.h"
#include "bn_sprite_animate_actions.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace mar
{
    class mar_enemy
    {

    public:
        /**
         * enemy constructor
         *
         * @param starting_position the location to start the enemy at
         * @param speed the pixels/frame the enemy moves at in each dimension
         */
        mar_enemy(bn::fixed_point starting_position, bn::fixed speed);

        // move the enemy
        void update();

        bn::rect &rect();

        bool isPassed();
        
        void set_position(bn::fixed_point position);

    private:
        // The sprite to display the enemy
        bn::sprite_ptr _sprite;
        bn::sprite_animate_action<3> _sprite_action;
        // The pixels/frame the enemy moves in each dimension
        bn::fixed _speed;
    // The rectangle used for collision detection
        bn::rect _rect;

    };

}

#endif