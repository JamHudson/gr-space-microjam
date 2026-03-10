#ifndef AXO_HITBOX_H
#define AXO_HITBOX_H

#include <bn_rect.h>
#include <bn_size.h>
#include <bn_sprite_ptr.h>

namespace axo {

class hitbox {
    public:
        hitbox(const bn::sprite_ptr& sprite, bn::size size);

        bn::rect rect() const;
        bool intersects(const hitbox& other) const;

    private:
        const bn::sprite_ptr _sprite;
        bn::size _size;
};
}

#endif