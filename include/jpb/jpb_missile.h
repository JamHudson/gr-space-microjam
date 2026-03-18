#ifndef JPB_MISSILE_H
#define JPB_MISSILE_H

#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_fixed_point.h>

namespace jpb {
    class jpb_missile {
        public:
            // constructor declaration
            jpb_missile(bn::fixed_point starting_position, bn::fixed speed, bn::size size);
            // update declaration
            void update();

            // Properties

            bn::sprite_ptr _sprite; 
            bn::fixed _speed; 
            bn::size _size;
            bn::rect _bounding_box;
    };
}

#endif