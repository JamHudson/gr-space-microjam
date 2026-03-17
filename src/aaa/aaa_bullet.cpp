#include <bn_fixed.h>
#include <bn_math.h>
#include <bn_log.h>

#include "aaa/aaa_bullet.h"
#include "bn_sprite_items_aaa_bullet.h"

namespace aaa
{

    aaa_Bullet::aaa_Bullet(bn::fixed_point starting_position, bn::fixed speed, bn::fixed angle) : _sprite(bn::sprite_items::aaa_bullet.create_sprite(starting_position)),
                                                                                                  _speed(speed),
                                                                                                  _angle(angle),
                                                                                                  _vx(-bn::degrees_lut_sin(_angle) * _speed),
                                                                                                  _vy(-bn::degrees_lut_cos(_angle) * _speed),
                                                                                                  _boundingBox(_sprite.x().round_integer(),
                                                                                                               _sprite.y().round_integer(),
                                                                                                               1, 1)
    {
    }

    void aaa_Bullet::update()
    {
        _sprite.set_x(_sprite.x() + _vx);
        _sprite.set_y(_sprite.y() + _vy);
        _boundingBox = bn::rect(_sprite.x().round_integer(),
                                _sprite.y().round_integer(),
                                1, 1);
    }
    bn::fixed_point aaa_Bullet::BulletPos()
    {
        return bn::fixed_point(_sprite.x(), _sprite.y());
    }
    bn::rect aaa_Bullet::getRect()
    {
        return _boundingBox;
    }
}