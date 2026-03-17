#ifndef SNO_BLACK_HOLE_H
#define SNO_BLACK_HOLE_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
// used the same include as aub/player.h for the animation include
#include <bn_sprite_animate_actions.h>
// testing the background here being tied to the spinning black hole
#include <bn_affine_bg_ptr.h>
#include "bn_affine_bg_items_background.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace sno
{

    /**
     * A black hole that attracts the player towards it.
     */
    class black_hole
    {
    public:
        /**
         * black_hole constructor
         *
         * @param position the location of the black hole
         */
        black_hole(bn::fixed_point position);

        /**
         * Gets the current position of the black hole.
         *
         * @return the black hole's position as a fixed_point
         */
        bn::fixed_point position() const;

        // called every frame to advance the spinning look animation of the black hole
        void update();

    private:
        // The sprite to display the black hole
        bn::sprite_ptr _sprite;
        // The position of the black hole
        bn::fixed_point _position;
        // The amount of frames in the entire animation
        bn::sprite_animate_action<3> _sprite_action;
        // The rotating background
        bn::affine_bg_ptr _background;
        bn::fixed _rotation = 0;
    };

}

#endif
