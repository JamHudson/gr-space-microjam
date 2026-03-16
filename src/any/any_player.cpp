#include "any_player.h"
#include "bn_keypad.h"

namespace any {
     player::player(bn::sprite_ptr sprite) : _sprite(sprite) {}

    void player::update(bn::span<const platform> platforms) {
        if (bn::keypad::left_held()) { _sprite.set_x(_sprite.x() - 2); }
        else if (bn::keypad::right_held()) { _sprite.set_x(_sprite.x() + 2); }

        _dy += 0.2;
        _sprite.set_y(_sprite.y() + _dy);


       



        if (_dy > 0) {
            for (const platform& p : platforms) {
                if (_sprite.y() >= p.y - 5 && _sprite.y() <= p.y + 2 &&
                    _sprite.x() >= p.x - 20 && _sprite.x() <= p.x + 20) {
                    
                    _dy = -4;
                    _sprite.set_y(p.y - 5);
                }
            }
        }
    }
    bn::fixed player::x() const { return _sprite.x(); }
    bn::fixed player::y() const { return _sprite.y(); }
}