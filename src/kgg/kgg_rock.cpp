#include "kgg/kgg_rock.h"

#include "bn_math.h"
#include "bn_display.h"
#include "bn_sprite_items_rock.h"

namespace kgg {

rock::rock(bn::fixed x, bn::fixed y)
: _sprite(bn::sprite_items::rock.create_sprite(x, y)) // position to create the rock
{
}

void rock::update()
{
    if(!_active)
    {
        return;
    }

    _sprite.set_y(_sprite.y() + 1); // rock moves downward by 1

    if(_sprite.y() > bn::display::height() / 2 + 8) // if the rock goes below the screen, hide it
    {
        _active = false;
        _sprite.set_visible(false);
    }
}

bool rock::active() const
{
    return _active;
}

bool rock::collides_with(bn::fixed player_x, bn::fixed player_y) const
{
    if(!_active)
    {
        return false;
    }

    bn::fixed dx = bn::abs(_sprite.x() - player_x);
    bn::fixed dy = bn::abs(_sprite.y() - player_y);

    // collision check if the rock hit the player or not
    return dx < 8 && dy < 8; 
}

}