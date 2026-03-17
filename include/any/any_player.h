#ifndef ANY_PLAYER_H
#define ANY_PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_fixed.h"
#include "bn_span.h"
#include "any_platform.h" 

namespace any {
    class player {
    public:
        player(bn::fixed x, bn::fixed y); 
        
        void update(bn::span<const platform> platforms);
        bn::fixed x() const;
        bn::fixed y() const;

    private:
        bn::sprite_ptr _sprite;
        bn::fixed _dy = 0;
    };
}
#endif