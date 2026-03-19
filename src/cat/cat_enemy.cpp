#include "cat/cat_enemy.h"
#include "bn_sprite_items_cat_enemy.h"
#include "bn_sound_items.h"

namespace cat
{
    cat_enemy::cat_enemy(bn::fixed x, bn::fixed y, bn::fixed speed) :
        _sprite(bn::sprite_items::cat_enemy.create_sprite(x, y)),
        _speed(speed)
    {
        _sprite.set_z_order(-1); // Appear above stars (lower z_order = in front)
    }

    void cat_enemy::update(const bn::fixed_point& player_position)
    {
        bn::fixed enemy_x = _sprite.x();
        bn::fixed enemy_y = _sprite.y();

        if(player_position.x() < enemy_x)
        {
            enemy_x -= _speed;
        }
        else if(player_position.x() > enemy_x)
        {
            enemy_x += _speed;
        }

        if(player_position.y() < enemy_y)
        {
            enemy_y -= _speed;
        }
        else if(player_position.y() > enemy_y)
        {
            enemy_y += _speed;
        }

        _sprite.set_position(enemy_x, enemy_y);
    }

    bn::fixed_point cat_enemy::position() const
    {
        return _sprite.position();
    }

    bool cat_enemy::collides_with(const bn::fixed_point& point) const
    {
        bn::fixed dx = point.x() - _sprite.x();
        bn::fixed dy = point.y() - _sprite.y();
        bn::fixed dist_sq = (dx * dx) + (dy * dy);
        
        return dist_sq < 16 * 16;
    }
}