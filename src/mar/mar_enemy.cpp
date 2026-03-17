#include "mar/mar_enemy.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_alien.h"

namespace mar
{
    /**
     * mar_enemy constructor
     *
     * @param starting_position the location to start the mar_enemy at
     * @param speed the pixels/frame the mar_enemy moves at in each dimension
     */
    mar_enemy::mar_enemy(
        bn::fixed_point starting_position,
        bn::fixed speed) : _sprite(bn::sprite_items::alien.create_sprite(starting_position)),
                           _sprite_action(
                                bn::create_sprite_animate_action_forever(
                                    _sprite, 16, bn::sprite_items::alien.tiles_item(),0,1,2
                                )
                            ),
                           _speed(speed),
                           _rect(bn::rect(
                               starting_position.x().round_integer(),
                               starting_position.y().round_integer(), 14, 14))
    {
    }

    bn::rect &mar_enemy::rect()
    {
        return _rect;
    }

    bool mar_enemy::isPassed()
    {
        return _sprite.x() <= MIN_X;
    }

    void mar_enemy::set_position(bn::fixed_point position)
    {
        _sprite.set_position(position);
    }

    // update the enemy's position by moving it left and updating the collision rectangle's position
    void mar_enemy::update()
    {
        _sprite_action.update();
        _sprite.set_x(_sprite.x() - _speed);
        _rect.set_position(_sprite.x().round_integer(), _sprite.y().round_integer());
    }
}