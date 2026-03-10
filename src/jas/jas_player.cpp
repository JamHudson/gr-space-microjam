#include "jas/jas_player.h"

#include <bn_math.h>
#include <bn_keypad.h>

#include "bn_sprite_items_templander.h"
#include "jas_player.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace jas
{

    /**
     * player constructor
     *
     * @param starting_position the location to start the player at
     * @param speed the pixels/frame the player moves at in each dimension
     */
    player::player(bn::fixed_point starting_position, bn::fixed vertical_speed, bn::fixed gravity) : _sprite(bn::sprite_items::templander.create_sprite(starting_position)),
                                                                                                     _vertical_speed(vertical_speed),
                                                                                                     _gravity(gravity),
                                                                                                     _engine_fired(false)
    {
    }
    /**
     * Reads from the d-pad and moves the player by one frame accordingly.
     */
    void player::update()
    {
        if (bn::keypad::a_held())
        {
            engineOn(BOOST_ACCELERATION);
        }
        if (crashed() || (on_surface() && at_crash_velocity()))
        {
            _crashed = true;
            _sprite.set_y(CRASH_Y);
            _vertical_speed = 0;
        }
        else
        {
            _vertical_speed += _gravity;
            _sprite.set_y(_sprite.y() + _vertical_speed);
        }
    }

    void player::engineOn(bn::fixed engine_thrust)
    {
        _vertical_speed -= engine_thrust;
    }

    bool player::on_surface() const
    {
        return _sprite.y() > CRASH_Y;
    }

    bool player::at_crash_velocity() const
    {
        return bn::abs(_vertical_speed) > CRASH_VELOCITY;
    }

    bool player::crashed() const
    {
        return _crashed;
    }
}