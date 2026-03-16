#ifndef KNC_PLANET_H
#define KNC_PLANET_H

#include "bn_fixed_point.h"
#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_display.h"

namespace knc {
// obtasble to use d-pad to move around to no collison or the game end
class planet {
public:

    static constexpr bn::fixed COLLISION_RADIUS = 6;
    // create a planet 
    planet( bn::fixed_point position, bn::fixed speed);

    void update();

    // return x y position
    bn::fixed_point position() const;
    // to check if planet is touching? the cat
    bool collides_with(bn::fixed_point other_pos, bn::fixed other_radius) const;
    // to check to remove planets that will no longer visible when keep moving
    bool off_screen() const;

private:
    bn::sprite_ptr _sprite;
    bn::fixed_point _position;
    bn::fixed _speed;
};

} // namespace knc

#endif