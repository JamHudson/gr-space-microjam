#ifndef CAT_STAR_H
#define CAT_STAR_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_optional.h"

namespace cat
{
    class star
    {
    public:
        star(int x, int y);

        void update();
        void collect();

        [[nodiscard]] bool is_collected() const { return _collected; }
        [[nodiscard]] bn::sprite_ptr& sprite() { return _sprite; }

    private:
        bn::sprite_ptr _sprite;
        bn::optional<bn::sprite_animate_action<4>> _idle_anim;
        bool _collected = false;
        int _burst_timer = 0;
    };
}

#endif