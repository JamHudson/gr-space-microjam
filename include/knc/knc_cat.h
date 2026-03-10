#ifndef KNC_CAT_H
#define KNC_CAT_H

#include "bn_fixed_point.h"
#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_display.h"


// my game user
namespace knc {

    class cat {

    // screen
    static constexpr bn::fixed MAX_X = bn::display::width() / 2;
    static constexpr bn::fixed MIN_X = -bn::display::width() / 2;
    static constexpr bn::fixed MAX_Y = bn::display::height() / 2;
    static constexpr bn::fixed MIN_Y = -bn::display::height() / 2;

    public:
    static constexpr bn::fixed COLLISION_RADIUS =6;

    cat(bn::fixed_point starting_position, bn::fixed speed);

    void update();

    // collision check
    bn::fixed_point position() const;
    // change the speed as scores increase
    void set_speed(bn::fixed speed);

    private:
    bn::sprite_ptr _sprite;
    bn::fixed _speed;
    bn::fixed_point _position;
    };
}





#endif