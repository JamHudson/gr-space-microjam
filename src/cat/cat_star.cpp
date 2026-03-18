#include "cat_star.h"
#include "bn_sprite_items_cat_star.h"

namespace cat
{
    star::star(int x, int y) :
        _sprite(bn::sprite_items::cat_star.create_sprite(x, y)),
        _idle_anim(bn::create_sprite_animate_action_forever(
            _sprite, 8, bn::sprite_items::cat_star.tiles_item(), 0, 1, 2, 3
        ))
    {
    }

    void star::update()
    {
        if (_collected)
        {
            // show burst frame for a few frames then hide
            if (_burst_timer > 0)
            {
                --_burst_timer;
                if (_burst_timer == 0)
                {
                    _sprite.set_visible(false);
                }
            }
            return;
        }

        _idle_anim->update();
    }

    void star::collect()
    {
        if (_collected) return;

        _collected = true;
        _idle_anim.reset();
        _sprite.set_tiles(bn::sprite_items::cat_star.tiles_item().create_tiles(4));
        _burst_timer = 8;
    }
}