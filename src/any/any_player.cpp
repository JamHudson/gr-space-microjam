#include "any_player.h"
#include "bn_keypad.h"
#include "bn_sprite_items_astronaut.h"

namespace any {

    // Initializer list sets up the sprite and defaults
    player::player(bn::fixed x, bn::fixed y) : 
        _sprite(bn::sprite_items::astronaut.create_sprite(x, y)),
        _dy(0)
    {
    }

   void player::update(bn::span<const platform> platforms) {
    // --- Horizontal Movement ---
    if (bn::keypad::left_held()) { 
        _sprite.set_x(_sprite.x() - 1.5); 
    }
    else if (bn::keypad::right_held()) { 
        _sprite.set_x(_sprite.x() + 1.5); 
    }

    // --- Gravity ---
    _dy += 0.15;
    _sprite.set_y(_sprite.y() + _dy);

    // --- Automatic Bounce Collision ---
    if (_dy > 0) { 
    for(const platform& p : platforms) {
        if (_sprite.y() >= p.y() - 6 && _sprite.y() <= p.y() + 2 &&
            _sprite.x() >= p.x() - 24 && _sprite.x() <= p.x() + 24) {
            _dy = -4.3; 
            _sprite.set_y(p.y() - 6); 
            break; 
        }
    }
    }
}
    bn::fixed player::x() const { return _sprite.x(); }
    bn::fixed player::y() const { return _sprite.y(); }
}