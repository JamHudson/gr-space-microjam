#ifndef AAA_BULLET_H
#define AAA_BULLET_H

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
namespace aaa
{
    class aaa_Bullet
    {
    public:
        aaa_Bullet(bn::fixed_point starting_position, bn::fixed speed, bn::fixed angle);

        void update();
        bn::fixed_point BulletPos();
        bn::rect getRect();

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;

        bn::fixed _speed;
        bn::fixed _angle;
        bn::fixed _vx;
        bn::fixed _vy;
        bn::rect _boundingBox;
    };
}
#endif