#include "reb_moon.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_reb_moon.h"
#include "bn_keypad.h"
#include "bn_math.h"

#include "bn_sound_items.h"

namespace reb
{
    static constexpr int base_speed = 1;

    moon::moon(bn::fixed earth_x, bn::fixed earth_y, bn::fixed orbit_radius, bn::fixed start_angle_degrees, bn::fixed speed_modifier) : 
        _moonSprite(bn::sprite_items::reb_moon.create_sprite(0,0)),
        _earth_x(earth_x),
        _earth_y(earth_y),
        _orbit_radius(orbit_radius),
        _angle(start_angle_degrees),
        _angular_speed(base_speed * speed_modifier) 
    {
        _update_sprite_position();
    }

    void moon::update()
    {

        // play sound effect on button press
        if(bn::keypad::right_pressed() || bn::keypad::left_pressed())
        {
            bn::sound_items::reb_space1.play();
        }

        if(bn::keypad::right_held())
        {
            _angle -= _angular_speed;
        }

        if(bn::keypad::left_held())
        {
            _angle += _angular_speed;
        }

        // keep angle within 0 - 360
        if (_angle < 0) { _angle += 360; }
        if (_angle >= 360 ) { _angle -= 360; }

        _update_sprite_position();
    }

    bn::fixed moon::x() const { return _moonSprite.x(); }
    bn::fixed moon::y() const { return _moonSprite.y(); }
    bn::fixed moon::angle() const { return _angle; }

    void moon::_update_sprite_position()
    {
        bn::fixed new_x = _earth_x + _orbit_radius * bn::degrees_cos(_angle);
        bn::fixed new_y = _earth_y + _orbit_radius * bn::degrees_sin(_angle);
        _moonSprite.set_position(new_x, new_y);
    }
}