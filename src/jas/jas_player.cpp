#include "jas/jas_player.h"

#include <bn_math.h>
#include <bn_keypad.h>
#include "bn_log.h"

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
                                                                                                     _crashed(false)
    {
    }
    /**
     * Moves the player based on vertical speed, changing when the boost button is held.
     */
    void player::update()
    {
        // While the boost button is pressed
        if (bn::keypad::a_held())
        {
            // Add BOOST_ACCELERATION to the player's speed.
            engineOn(_gravity*2);
        }
        // If the player has already crashed, or is about to
        if (crashed() || (on_surface() && at_crash_velocity()))
        {
            // Indicate they are crashed and keep them immobile at surface height
            _crashed = true;
            _sprite.set_y(CRASH_Y);
            _vertical_speed = 0;
        }
        else
        {
            // Else, pull the player down by gravity
            _vertical_speed += _gravity;
            // Move the player based on their current speed.
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