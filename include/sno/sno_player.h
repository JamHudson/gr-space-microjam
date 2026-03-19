#ifndef SNO_PLAYER_H // Include guard must start with the 3-letter id
#define SNO_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_sound_items.h>

// All game functions/classes/variables/constants scoped to the namespace
namespace sno
{

    /**
     * A character controlled with the d-pad.
     */
    class player
    {
        // The bounds of the screen
        static constexpr int MAX_X = bn::display::width() / 2;
        static constexpr int MIN_X = -bn::display::width() / 2;
        static constexpr int MAX_Y = bn::display::height() / 2;
        static constexpr int MIN_Y = -bn::display::height() / 2;

    public:
        /**
         * player constructor
         *
         * @param starting_position the location to start the player at
         * @param speed the pixels/frame the player moves at in each dimension
         */
        player(bn::fixed_point starting_position, bn::fixed speed);

        /**
         * Reads from the d-pad and moves the player by one frame accordingly.
         */
        void update();

        /**
         * Simple attraction function to start out with.
         * Moves the player towards the blackhole at a fixed rate
         * @param bh_position the position of the black hole to be attracted to
         */
        void attraction(bn::fixed_point bh_position);

        /**
         * Screen wrap function to wrap the player to the opposite side, left to right,
         */
        void screenWrap();

        /**
         * Returns whether the player has left the screen
         *
         * @return true if the player has left the screen, false if it is still on the screen
         */
        bool out_of_bounds() const;
        /**
         * Returns the player's current position
         */
        bn::fixed_point position() const;

        /**
         * Returns whether the player has collided with a given position
         *
         * @param other_position position to check collision against
         * @param perimeter how many pixels counts as a collision
         */
        bool collides_with(bn::fixed_point other_position, int perimeter) const;

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // The pixels/frame the player moves in each dimension
        bn::fixed _speed;

        int _movement_sound_timer = 0;
    };

}

#endif
