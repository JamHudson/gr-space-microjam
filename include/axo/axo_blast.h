#ifndef AXO_BLAST_H // Include guard must start with the 3-letter id
#define AXO_BLAST_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_size.h>
#include <bn_display.h>


// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

    static constexpr bn::size BLAST_SIZE = {16, 16};

class blast {

    public:
        /**
         * blast constructor
         * 
         * @param starting_x the x coordinate to start the bubble at
         * @param starting_y the y coordinate to start the bubble at
         * @param bubble_size the size of the bubble
         */
        blast(bn::fixed starting_x, bn::fixed starting_y, bn::size blast_size);

        void update();

        bn::fixed y() const {
            return _sprite.y();
        }
    
    private:
        // The sprite to display the blast
        bn::sprite_ptr _sprite;
        //size
        bn::size _size;
};

}

#endif