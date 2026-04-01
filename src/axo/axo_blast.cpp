#include "axo/axo_blast.h"

#include "bn_sprite_items_axo_blast.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace axo {

    /**
        * blast constructor
        * 
        * @param starting_x the x coordinate to start the blast at
        * @param starting_y the y coordinate to start the blast at
        */
    blast::blast(bn::fixed starting_x, bn::fixed starting_y) : 
        _sprite(bn::sprite_items::axo_blast.create_sprite(bn::fixed_point(starting_x, starting_y))),
        _frames_remaining(8)
    {
    }

    void blast::update() {
        --_frames_remaining;
    }

    bool blast::active_blast() const {
        return _frames_remaining;
    }
}