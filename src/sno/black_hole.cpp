#include "black_hole.h"

#include "bn_sprite_items_black_hole.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace sno
{

    /**
     * black_hole constructor
     *
     * @param position the location of the black hole
     */
    black_hole::black_hole(bn::fixed_point position)
        : _sprite(bn::sprite_items::black_hole.create_sprite(position)),
          _position(position)
    {
    }

    /**
     * Gets the current position of the black hole.
     *
     * @return the black hole's position as a fixed_point
     */
    bn::fixed_point black_hole::position() const
    {
        return _position;
    }

}
