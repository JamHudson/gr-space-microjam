#ifndef AXO_BLAST_H // Include guard must start with the 3-letter id
#define AXO_BLAST_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>


// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

class blast {

    public:
        /**
         * blast constructor
         * 
         * @param starting_x the x coordinate to start the blast at
         * @param starting_y the y coordinate to start the blast at
         */
        blast(bn::fixed starting_x, bn::fixed starting_y);

        void update();

        bool active_blast() const;
        
    
    private:
        // The sprite to display the blast
        bn::sprite_ptr _sprite;
        int _frames_remaining;
};

}

#endif