#include "aaa/aaa_enemy.h"
#include <bn_math.h>
#include "bn_sprite_items_aaa_enemy.h"
#include <bn_rect.h>
#include "bn_sprite_items_aaa_asteroid_destroyed.h"

namespace aaa
{
    /**
     * enemy constructor
     *
     * @param starting_position the location to start the enemy at
     * @param speed the pixels/frame the enemy moves at in each dimension
     */
    aaa_enemy::aaa_enemy(bn::fixed_point starting_position, bn::fixed speed) : _sprite(bn::sprite_items::aaa_enemy.create_sprite(starting_position)),
                                                                               _speed(speed),
                                                                               _boundingBox(_sprite.x().round_integer(),
                                                                                            _sprite.y().round_integer(),
                                                                                            15, 15),
                                                                               _sprite_action(bn::create_sprite_animate_action_once(
                                                                                   _sprite, 16, bn::sprite_items::aaa_asteroid_destroyed.tiles_item(), 0, 1, 2, 3))
    {
        _sprite.set_z_order(3); // its sprite layer order under players
    }

    void aaa_enemy::update()
    {
        if (isDestroyed)
        {
            if (!_sprite_action.done())
            {
                _sprite_action.update();
            }
            return;
        }

        // if player is always {0,0} this is fine instead of the commented code below, minusing a 0 could be problematic
        // bn::fixed dist = sqrt((_sprite.x() * _sprite.x() - 0) + (_sprite.y() * _sprite.y() - 0));
        bn::fixed dist = sqrt((_sprite.x() * _sprite.x()) + (_sprite.y() * _sprite.y()));

        if (dist > 0)
        {
            _sprite.set_position(_sprite.position() - (_sprite.position() / dist) * _speed);
            _boundingBox = bn::rect(_sprite.x().round_integer(),
                                    _sprite.y().round_integer(),
                                    15, 15);
        }
    }

    bn::rect aaa_enemy::getRect()
    {
        return _boundingBox;
    }

    void aaa::aaa_enemy::destroyedAnimation()
    {
        if (!isDestroyed)
        {
            isDestroyed = true;
            _sprite_action = bn::create_sprite_animate_action_once(_sprite, 8, bn::sprite_items::aaa_asteroid_destroyed.tiles_item(), 0, 1, 2, 3);
        }
    }
    bool aaa::aaa_enemy::is_destroyed()
    {
        return isDestroyed;
    }
    bool aaa::aaa_enemy::animation_done()
    {
        return _sprite_action.done();
    }
}