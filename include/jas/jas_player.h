#ifndef JAS_PLAYER_H // Include guard must start with the 3-letter id
#define JAS_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>

// All game functions/classes/variables/constants scoped to the namespace test
namespace jas
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

        // The Velocity the player can land at before crashing
        static constexpr int CRASH_VELOCITY = 30;
        static constexpr bn::fixed BOOST_ACCELERATION = 0.05;

    public:
        /**
         * player constructor
         *
         * @param starting_position the location to start the player at
         * @param speed the pixels/frame the player moves at in each dimension
         */
        player(bn::fixed_point starting_position, bn::fixed vertical_speed, bn::fixed gravity, bool engine_fired);

        /**
         * Reads from the d-pad and moves the player by one frame accordingly.
         */
        void update();

        /**
         * When actived, engineOn will add increase the player's y axis position for a set amount of time
         */
        void engineOn(bn::fixed engine_thrust);

        /**
         * Returns whether the player has left the screen
         *
         * @return true if the player has left the screen, false if it is still on the screen
         */
        bool out_of_bounds() const;

        /**
         * Returns whether the player has left the screen ON THE BOTTOM
         *
         * @return true if the player has left the screen, false if it is still on the screen
         */
        bool on_surface() const;

        /**
         * Returns whether the player is moving fast enough to crash
         *
         * @return true if the player can crash, false if it can't
         */
        bool at_crash_velocity() const;

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // The pixels/frame the player moves in each dimension
        bn::fixed _vertical_speed;

        bn::fixed _gravity;
        bool _engine_fired;
    };

}

#endif