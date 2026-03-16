#ifndef BAL_ROCKS_H
#define BAL_ROCKS_H

#include <bn_display.h>
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_size.h>

#include "bal_screen_size.h"

namespace bal{

class rock{

    private:
        bn::sprite_ptr _sprite;
        bn::fixed _speed;
        bn::size _size;

    public:
        rock(int starting_x, int starting_y, bn::fixed speed, bn::size rock_size);

        bool update();
        
        bn::rect bounding_box;
    
    
       
};

}

#endif