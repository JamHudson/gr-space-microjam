#ifndef JAS_PLAYER_H // Include guard must start with the 3-letter id
#define JAS_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>

// All game functions/classes/variables/constants scoped to the namespace test
namespace jas
{

    /**
     * A character controlled with the B button, influenced by gravity.
     */
    class player
    {
        // The bounds of the screen
        static constexpr bn::fixed CRASH_Y = 31;

        // The Velocity the player can land at before crashing
        static constexpr bn::fixed CRASH_VELOCITY = 1;
        
        // The Acceleration applied to the player while boosting
        static constexpr bn::fixed BOOST_ACCELERATION = 0.05;

    public:
        /**
         * player constructor
         *
         * @param starting_position the location to start the player at
         * @param speed the pixels/frame the player moves at in each dimension
         * @param vertical_speed the initial vertical speed of the player
         * @param gravity the influence of gravity on the character
         */
        player(bn::fixed_point starting_position, bn::fixed vertical_speed, bn::fixed gravity);

        /**
         * Moves the player based on vertical speed, changing when the boost button (B) is held.
         */
        void update();

        /**
         * When actived, engineOn will increase the player's vertical speed upwards (-y direction)
         */
        void engineOn(bn::fixed engine_thrust);

        /**
         * Returns whether the player has gone beneath the surface (CRASH_Y)
         *
         * @return true if the player is under/on the surface, false if it is not
         */
        bool on_surface() const;

        /**
         * Returns whether the player is moving fast enough to crash
         *
         * @return true if the player can crash, false if it can't
         */
        bool at_crash_velocity() const;

        /**
         * Returns whether the player is crashed, i.e, has lost.
         *
         * @return true if the player has crashed, false it hasn't
         */
        bool crashed() const;

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // The pixels/frame the player moves in each dimension
        bn::fixed _vertical_speed;

        bn::fixed _gravity;
        bool _crashed;
    };

}

#endif