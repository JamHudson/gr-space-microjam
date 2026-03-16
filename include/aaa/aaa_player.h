#ifndef AAA_PLAYER_H
#define AAA_PLAYER_H

#include <bn_sprite_ptr.h>
#include <bn_rect.h>

namespace aaa
{
    class aaa_Player
    {
    public:
        aaa_Player(bn::fixed_point starting_position);

        void update();

        bn::fixed getAngle();
        bn::rect getRect();

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // how many degrees the player rotates per button press
        int _rotation_speed;
        bn::rect _boundingBox;
    };
}
#endif