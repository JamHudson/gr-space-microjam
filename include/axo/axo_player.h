#ifndef AXO_PLAYER_H // Include guard must start with the 3-letter id
#define AXO_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>
#include <bn_rect.h>
#include <bn_size.h>

// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

static constexpr bn::size PLAYER_SIZE = {8, 16};

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
        player(bn::fixed_point starting_position, bn::fixed speed, bn::size player_size);

        /**
         * Reads from the d-pad and moves the player by one frame accordingly.
         */
        void update();

        bool still_alive() const;
    
    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // The pixels/frame the player moves in each dimension
        bn::fixed _speed;
        bn::size _size;
        bn::rect _bounding_box;
};

}

#endif