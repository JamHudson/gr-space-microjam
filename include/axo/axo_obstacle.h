#ifndef AXO_OBSTACLE_H // Include guard must start with the 3-letter id
#define AXO_OBSTACLE_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_display.h>

#include "axo/axo_player.h"
#include "axo/axo_hitbox.h"


// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

    static constexpr bn::size OBSTACLE_SIZE = {16, 16};

/**
 * A sprite flying through space!
 */
class obstacle {

    public:
        /**
         * player constructor
         * 
         * @param starting_position the location to start the obstacle at
         * @param speed the pixels/frame the obstacle moves at in each dimension
         */
        obstacle(bn::fixed starting_x, bn::fixed starting_y, bn::fixed speed,bn::size obstacle_size);

        /**
         * Player helps with updating enemy
         */
        void update(player& player);

        const hitbox& get_hitbox() const;

        //Out of bounds not needed for obstacle, meant to leave screen anyways
    
    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // The pixels/frame the player moves in each dimension
        bn::fixed _speed;
        //size
        bn::size _size;
        hitbox _hitbox;
};

}

#endif