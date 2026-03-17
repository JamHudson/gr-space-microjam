#ifndef ANY_PLATFORM_H
#define ANY_PLATFORM_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

namespace any {

class platform {
public:
    platform(bn::fixed x, bn::fixed y);
    platform();

    void set_position(bn::fixed x, bn::fixed y);
    
    bn::fixed x() const;
    bn::fixed y() const;

private:
    bn::fixed _x;
    bn::fixed _y;
    bn::sprite_ptr _sprite;
};

}

#endif