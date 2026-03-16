#ifndef AUB_PLAYER_H // Include guard must start with the 3-letter id
#define AUB_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_animate_actions.h>
#include <bn_display.h>


// All game functions/classes/variables/constants scoped to the namespace
namespace aub {

/**
 * A character controlled with the d-pad.
 */
class player {
        // The bounds of the screen
        static constexpr int MAX_X = bn::display::width() / 2;
        static constexpr int MIN_X = - bn::display::width() / 2;
        static constexpr int MAX_Y = bn::display::height() / 2;
        static constexpr int MIN_Y = - bn::display::height() / 2;

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
         * Returns whether the player has left the screen
         * 
         * @return true if the player has left the screen, false if it is still on the screen
         */
        bool out_of_bounds() const;
    
    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        bn::sprite_animate_action<4> _sprite_action;
        // The pixels/frame the player moves in each dimension
        bn::fixed _speed;

        /**
         * Reads from the d-pad and moves the player by one frame accordingly.
         */
        void _update_position();
        /**
         * Reads from the d-pad and sets direction sprites is pointing.
         * Regardless of direction, updates the sprite animation action.
         */
        void _update_animation();
        
};

}

#endif
