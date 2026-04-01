#ifndef AXO_HITBOX_H
#define AXO_HITBOX_H

#include <bn_fixed_point.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>

namespace axo {

class hitbox {
    public:
        // The offset of sprites is 0, 0 by default. Sprites without need of it can just use that.
        // Our player sprite does need the offset.
        hitbox(const bn::sprite_ptr& sprite, bn::size size, bn::fixed_point 
            offset = bn::fixed_point(0, 0));

        bn::rect rect() const;
        bool intersects(const hitbox& other) const;

    private:
        bn::sprite_ptr _sprite;
        bn::size _size;
        bn::fixed_point _offset;
};
}

#endif