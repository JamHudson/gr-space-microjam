#include "kgg/kgg_rock.h"

#include "bn_math.h"
#include "bn_display.h"
#include "bn_sprite_items_rock.h"

namespace kgg {

rock::rock(bn::fixed x, bn::fixed y, bn::fixed speed)
: _sprite(bn::sprite_items::rock.create_sprite(x, y)), // position to create the rock
  _speed(speed),
  _animation(                                   
      bn::create_sprite_animate_action_forever( 
          _sprite,
          12,                                    
          bn::sprite_items::rock.tiles_item(),
          0, 1))     
{
}

void rock::update()
{
    if(!_active)
    {
        return;
    }

    _animation.update(); // updating animation every frame

    _sprite.set_y(_sprite.y() + _speed); // rock moves downward by speed

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