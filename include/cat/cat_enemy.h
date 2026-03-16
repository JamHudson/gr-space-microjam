#ifndef CAT_ENEMY_H
#define CAT_ENEMY_H

#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "mj/mj_game_data.h"

namespace cat
{
    class cat_enemy
    {
    public:
        cat_enemy(bn::fixed x, bn::fixed y, bn::fixed speed);

        void update(const bn::fixed_point& player_position);
        
        bn::fixed_point position() const;
        
        bool collides_with(const bn::fixed_point& point) const;

    private:
        bn::sprite_ptr _sprite;
        bn::fixed _speed;
    };
}

#endif // CAT_ENEMY_H