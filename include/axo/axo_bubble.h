#ifndef AXO_BUBBLE_H // Include guard must start with the 3-letter id
#define AXO_BUBBLE_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_rect.h>
#include <bn_display.h>

#include "axo/axo_hitbox.h"


// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

    static constexpr bn::size BUBBLE_SIZE = {8, 8};
    static constexpr bn::fixed BUBBLE_SPEED = 2;

class bubble {

    public:
        /**
         * bubble constructor
         * 
         * @param starting_x the x coordinate to start the bubble at
         * @param starting_y the y coordinate to start the bubble at
         * @param bubble_speed the pixels/frame the bubble moves at in each dimension
         * @param bubble_size the size of the bubble
         */
        bubble(bn::fixed starting_x, bn::fixed starting_y, bn::fixed bubble_speed, bn::size bubble_size);

        void update();

        bn::fixed y() const {
            return _sprite.y();
        }

        bn::fixed x() const {
            return _sprite.x();
        }

        const hitbox& get_hitbox() const;
    
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