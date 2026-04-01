#ifndef MAR_PLAYER_H
#define MAR_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include "bn_sprite_animate_actions.h"

#include "bn_rect.h"
#include "mar/mar_bounds.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace mar
{

    /**
     * A character controlled with the d-pad.
     */
    class mar_player
    {

    public:
        /**
         * player constructor
         *
         * @param starting_position the location to start the player at
         * @param speed the pixels/frame the player moves at in each dimension
         */
        mar_player(bn::fixed_point starting_position, bn::fixed speed);

        /**
         * returns
         */
        bn::rect &rect()
        {
            return _rect;
        }

        /**
         * Reads from the d-pad and moves the player by one frame accordingly.
         */
        void update();

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // Only 5 tiles but added 6th ghost tile for animation math
        bn::sprite_animate_action<6> _sprite_action;

        // The pixels/frame the player moves in each dimension
        bn::fixed _speed;
        bn::rect _rect;
    };

}

#endif