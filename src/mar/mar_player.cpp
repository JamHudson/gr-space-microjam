#include "mar/mar_player.h"

#include <bn_keypad.h>
#include <bn_rect.h>
#include "bn_sprite_items_droid.h"
#include "bn_sound_items.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace mar
{

    /**
     * mar_player constructor
     *
     * @param starting_position the location to start the mar_player at
     * @param speed the pixels/frame the mar_player moves at in each dimension
     */
    mar_player::mar_player(
        bn::fixed_point starting_position,
        bn::fixed speed) : _sprite(bn::sprite_items::droid.create_sprite(starting_position)),
                           _sprite_action(
                                bn::create_sprite_animate_action_forever(
                                    _sprite, 8, bn::sprite_items::droid.tiles_item(),0,1,2,3,4,5
                                )  // Only tiles for #0-#4 but added #5 ghost tile for animation math
                            ),
                           _speed(speed),
                           _rect(
                               bn::rect(
                                   starting_position.x().round_integer(),
                                   starting_position.y().round_integer(), 10, 14))
    {
    }

    /**
     * Reads from the d-pad and moves the mar_player by one frame accordingly.
     */
    void mar_player::update()
    {
        bool isFrameEven = _sprite_action.current_index()%2 == 0;
        int framesLeft = _sprite_action.wait_updates();

        // buffer to avoid ghost frame
        if(_sprite_action.current_index() == 5)_sprite_action.set_current_index(0);
        // If up is held moves up. If down is held moves down. Otherwise, moves down at a slower speed to simulate gravity.

        if((_sprite.y() < MAX_Y && ( // If below then Floor
                (!bn::keypad::down_held() && !bn::keypad::up_held()) // no buttons pressed
                || (bn::keypad::down_held() && bn::keypad::up_held()) // both buttons pressed
            ) ) || _sprite.y() <= MIN_Y // Or At/Above Ceiling
        )
        {
            _sprite_action.set_current_index(0);
            _sprite_action.set_wait_updates(framesLeft);
            _sprite.set_y(_sprite.y() + _speed/4);
        }
        else if (bn::keypad::up_held() && _sprite.y() > MIN_Y)
        {
            //  SFX for when player up_held
            if (bn::keypad::up_pressed())
            {
                bn::sound_items::mar_erase.play();
            }
            _sprite_action.set_current_index(isFrameEven?4:3);
            _sprite_action.set_wait_updates(framesLeft);
            _sprite.set_y(_sprite.y() - _speed);
        }
        else if (bn::keypad::down_held() && _sprite.y() < MAX_Y)
        {
            //  SFX for when player down_held
            if (bn::keypad::down_pressed())
            {
                bn::sound_items::mar_erase.play();
            }
            _sprite_action.set_current_index(isFrameEven?2:1);
            _sprite_action.set_wait_updates(framesLeft);
            _sprite.set_y(_sprite.y() + _speed);
        } 
        else if (_sprite.y() >= MAX_Y)
        {
            _sprite_action.set_current_index(0);
            _sprite_action.set_wait_updates(framesLeft);
        }
        _sprite_action.update();
        _rect.set_position(_sprite.x().round_integer(), _sprite.y().round_integer());
    }
}