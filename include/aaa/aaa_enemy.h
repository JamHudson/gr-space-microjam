#ifndef AAA_ENEMY_H
#define AAA_ENEMY_H

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_sprite_animate_actions.h>

namespace aaa
{
    class aaa_enemy
    {
    public:
        aaa_enemy(bn::fixed_point starting_position, bn::fixed speed);

        void update();
        bn::rect getRect();
        void destroyedAnimation();
        bool is_destroyed();
        bool animation_done();

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // The pixels/frame the player moves in each dimension
        bn::fixed _speed;
        bn::rect _boundingBox;
        bn::sprite_animate_action<4> _sprite_action;
        bool isDestroyed = false;
    };
}
#endif