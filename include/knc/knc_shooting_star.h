#ifndef KNC_SHOOTING_STAR_H
#define KNC_SHOOTING_STAR_H

#include "bn_fixed_point.h"
#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_display.h"
#include "bn_sprite_animate_actions.h"

// FLY ACROSS THE SCREEN TO INCREASE DIFFICULTY
namespace knc {
    class shooting_star {
        static constexpr bn::fixed OFFSCREEN_X = bn::display::width() / 2 + 32;

public:
    static constexpr bn::fixed COLLISION_RADIUS = 10;

    // create a shooting star at a given position with a given speed
    shooting_star(bn::fixed_point position, bn::fixed speed);

    // move shooting star horizontally once per frame
    void update();

    // return current position for collision detection
    bn::fixed_point position() const;

    // check if shooting star is touching the cat
    bool collides_with(bn::fixed_point other_pos, bn::fixed other_radius) const;

    // check if shooting star has gone off the right side of the screen
    bool off_screen() const;

private:
    bn::sprite_ptr _sprite;

    // 4 frame looping animation like planet
    bn::sprite_animate_action<4> _animation;
    bn::fixed_point _position;
    bn::fixed _speed;
};

} // namespace knc



#endif




