#include "axo/axo_obstacle.h"

#include "bn_sprite_items_axo_obstacle.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace axo
{

    /**
     * player constructor
     *
     * @param starting_position the location to start the player at
     * @param speed the pixels/frame the player moves at in each dimension
     */
    obstacle::obstacle(bn::fixed starting_x, bn::fixed starting_y, bn::fixed speed, bn::size obstacle_size) :
        _sprite(bn::sprite_items::axo_obstacle.create_sprite(bn::fixed_point(starting_x, starting_y))),
        _speed(speed),
        _size(obstacle_size),
        _hitbox(_sprite, _size)
    {
    }

    void obstacle::update([[maybe_unused]] player &player)
    {
        // moves obstacles downwards
        _sprite.set_y(_sprite.y() + _speed * 1.2);
        // rotate the sprite as it moves
        if(_sprite.rotation_angle() >= 360) {
            _sprite.set_rotation_angle(0);
        }
        _sprite.set_rotation_angle(_sprite.rotation_angle() + 5);

    }

    const hitbox &obstacle::get_hitbox() const
    {
        return _hitbox;
    }

}