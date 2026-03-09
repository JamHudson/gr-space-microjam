#include "jas/jas_player.h"

#include <bn_keypad.h>

#include "bn_sprite_items_jas_dot.h"
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
    player::player(bn::fixed_point starting_position, bn::fixed vertical_speed, bn::fixed gravity, bool engine_fired) : _sprite(bn::sprite_items::jas_dot.create_sprite(starting_position)),
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
            engineOn(.05);
        }
        _vertical_speed += _gravity;
        _sprite.set_y(_sprite.y() + _vertical_speed);
    }

    void player::engineOn(bn::fixed engine_thrust)
    {
        _vertical_speed -= engine_thrust;
    }

    /**
     * Returns whether the player has left the screen
     *
     * @return true if the player has left the screen, false if it is still on the screen
     */
    bool player::out_of_bounds() const
    {
        return _sprite.x() > MAX_X ||
               _sprite.x() < MIN_X ||
               _sprite.y() > MAX_Y ||
               _sprite.y() < MIN_Y;
    }
}