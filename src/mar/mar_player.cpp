#include "mar/mar_player.h"

#include <bn_keypad.h>
#include <bn_rect.h>

#include "bn_sprite_items_square.h"
#include "bn_sprite_items_droid.h"

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
                                    _sprite, 16, bn::sprite_items::droid.tiles_item(),0,3,4
                                )
                            ),
                           _speed(speed),
                           _rect(
                               bn::rect(
                                   starting_position.x().round_integer(),
                                   starting_position.y().round_integer(), 10, 14))
    {}

    /**
     * Reads from the d-pad and moves the mar_player by one frame accordingly.
     */
    void mar_player::update()
    {

        if (bn::keypad::down_held() && _sprite.y() < MAX_Y)
        {
            _sprite.set_y(_sprite.y() + _speed);
            _sprite_action = bn::create_sprite_animate_action_forever(
                _sprite,16,bn::sprite_items::droid.tiles_item(),1,2
            );
        }

        // If up is held moves up. If down is held moves down. Otherwise, moves down at a slower speed to simulate gravity.
        if (bn::keypad::up_held() && _sprite.y() > MIN_Y)
        {
            _sprite.set_y(_sprite.y() - _speed);
            _sprite_action = bn::create_sprite_animate_action_forever(
                _sprite,1,bn::sprite_items::droid.tiles_item(),3,4
            );
        }
        else
        {
            _sprite.set_y(_sprite.y() + _speed/4);
            // _sprite_action = bn::create_sprite_animate_action_forever(
            //     _sprite, 16, bn::sprite_items::droid.tiles_item(),0,1);
        }

        _sprite_action.update();
        _rect.set_position(_sprite.x().round_integer(), _sprite.y().round_integer());
    }
}