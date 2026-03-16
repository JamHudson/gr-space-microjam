#ifndef BAL_SCREEN_SIZE_H
#define BAL_SCREEN_SIZE_H

#include <bn_display.h>

namespace bal{
    //GBA screen size
    static constexpr int MAX_X = bn::display::width() / 2;
    static constexpr int MIN_X = - bn::display::width() / 2;
    static constexpr int MAX_Y = bn::display::height() / 2;
    static constexpr int MIN_Y = - bn::display::height() / 2;
}

#endif