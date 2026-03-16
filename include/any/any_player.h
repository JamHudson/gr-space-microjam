#ifndef ANY_PLAYER_H
#define ANY_PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_fixed.h"
#include "bn_span.h"

namespace any {

struct platform {
    bn::fixed x;
    bn::fixed y;
};

class player {
public:
    player(bn::sprite_ptr sprite);

    void update(bn::span<const platform> platforms); 

    bn::fixed x() const;
    bn::fixed y() const;
        

private:
    bn::sprite_ptr _sprite;
    bn::fixed _dy = 0;
};

}

#endif