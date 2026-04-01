#include "sno_player.h"

#include <bn_keypad.h>

#include "bn_sprite_items_sno_dot.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace sno
{

    /**
     * player constructor
     *
     * @param starting_position the location to start the player at
     * @param speed the pixels/frame the player moves at in each dimension
     */
    player::player(bn::fixed_point starting_position, bn::fixed speed) : _sprite(bn::sprite_items::sno_dot.create_sprite(starting_position)),
                                                                         _speed(speed)
    {
    }

    /**
     * Reads from the d-pad and moves the player by one frame accordingly.
     */
    void player::update()
    {
        bool moving = false;

            if (bn::keypad::left_held())
        {
            _sprite.set_x(_sprite.x() - _speed);
            moving = true;
        }
        if (bn::keypad::right_held())
        {
            _sprite.set_x(_sprite.x() + _speed);
            moving = true;
        }
        if (bn::keypad::up_held())
        {
            _sprite.set_y(_sprite.y() - _speed);
            moving = true;
        }
        if (bn::keypad::down_held())
        {
            _sprite.set_y(_sprite.y() + _speed);
            moving = true;
        }
        if (moving)
        {
            if (_movement_sound_timer == 0)
            {
                bn::sound_items::sno_ufo_sound.play();
            }
            _movement_sound_timer++;
            // should retrigger the sound every 30 frames
            if (_movement_sound_timer >= 30)
            {
                _movement_sound_timer = 0;
            }
        }
        else
        {
            _movement_sound_timer = 0;
        }
    }

    void player::screenWrap()
    {
        bn::fixed_point pos = _sprite.position();
        if (pos.x() < MIN_X)
        {
            _sprite.set_x(MAX_X);
        }
        else if (pos.x() > MAX_X)
        {
            _sprite.set_x(MIN_X);
        }
        if (pos.y() < MIN_Y)
        {
            _sprite.set_y(MAX_Y);
        }
        else if (pos.y() > MAX_Y)
        {
            _sprite.set_y(MIN_Y);
        }
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

    void player::attraction(bn::fixed_point bh_position)
    {
        bn::fixed_point pos = _sprite.position();

        if (pos.x() < bh_position.x())
        {
            _sprite.set_x(pos.x() + .75);
        }
        else if (pos.x() > bh_position.x())
        {
            _sprite.set_x(pos.x() - .75);
        }

        if (pos.y() < bh_position.y())
        {
            _sprite.set_y(pos.y() + .75);
        }
        else if (pos.y() > bh_position.y())
        {
            _sprite.set_y(pos.y() - .75);
        }
    }

    bn::fixed_point player::position() const
    {
        return _sprite.position();
    }

    bool player::collides_with(bn::fixed_point other_position, int perimeter) const
    {
        bn::fixed dx = _sprite.x() - other_position.x();
        bn::fixed dy = _sprite.y() - other_position.y();

        // Check if within a square bounding box around the black hole
        return (dx > -perimeter && dx < perimeter) &&
               (dy > -perimeter && dy < perimeter);
    }
}
