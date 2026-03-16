#include <bn_keypad.h>

#include "aaa/aaa_player.h"
#include "bn_sprite_items_aaa_player.h"
#include <bn_rect.h>
namespace aaa
{

    aaa_Player::aaa_Player(bn::fixed_point starting_position) : _sprite(bn::sprite_items::aaa_player.create_sprite(starting_position)),
                                                                _rotation_speed(4),
                                                                _boundingBox(_sprite.x().round_integer(),
                                                                             _sprite.y().round_integer(),
                                                                             8,
                                                                             8)

    {
        _sprite.set_z_order(1); // make player sprite appear above enemy
    }

    void aaa_Player::update()
    {
        // rotate player
        if (bn::keypad::left_held())
        {
            if (_sprite.rotation_angle() >= 360)
            {
                _sprite.set_rotation_angle(0);
            }
            _sprite.set_rotation_angle(_sprite.rotation_angle() + _rotation_speed);
        }
        if (bn::keypad::right_held())
        {
            if (_sprite.rotation_angle() <= 0)
            {
                _sprite.set_rotation_angle(360);
            }
            _sprite.set_rotation_angle(_sprite.rotation_angle() - _rotation_speed);
        }
    }

    bn::fixed aaa_Player::getAngle()
    {
        return _sprite.rotation_angle();
    }

    bn::rect aaa_Player::getRect()
    {
        return _boundingBox;
    }
}