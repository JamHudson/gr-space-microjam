#ifndef KNC_ENEMY_H
#define KNC_ENEMY_H

#include "bn_fixed_point.h"
#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_display.h"

/* Enemy sprite — moves horizontally across the screen
Spawns from left or right edge, travels to the opposite side
*/
namespace knc {

class enemy {
public:
    static constexpr bn::fixed COLLISION_RADIUS = 8;

    enemy(bn::fixed_point position, bn::fixed speed, int direction);

    void update();
    bn::fixed_point position() const;

    //collision with cat
    bool collides_with(bn::fixed_point other_pos, bn::fixed other_radius) const;
    bool off_screen() const;

private:
    bn::sprite_ptr  _sprite;
    bn::fixed_point _position;
    bn::fixed       _speed;
    int             _direction; 
};

} // namespace knc

#endif