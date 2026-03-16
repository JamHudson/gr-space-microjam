#ifndef SNO_BLACK_HOLE_H
#define SNO_BLACK_HOLE_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>

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

    private:
        // The sprite to display the black hole
        bn::sprite_ptr _sprite;
        // The position of the black hole
        bn::fixed_point _position;
    };

}

#endif
