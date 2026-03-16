#include "bal/bal_rocks.h"
#include "bn_sprite_items_bal_square.h"

namespace bal{
    rock::rock(int starting_x, int starting_y, bn::fixed rock_speed, bn::size rock_size) :
        _sprite(bn::sprite_items::bal_square.create_sprite(starting_x, starting_y)),
        _speed(rock_speed),
        _size(rock_size),
        bounding_box(bn::rect(starting_x, starting_y, rock_size.width(), rock_size.height()))
        {}

    bool rock::update(){
        _sprite.set_y(_sprite.y() + _speed);
        bounding_box = bn::rect(
            _sprite.x().round_integer(),
            _sprite.y().round_integer(),
            _size.width(),
            _size.height()
        );

        //checks if rock has reached the bottom
        return _sprite.y() > MAX_Y;
    }
}