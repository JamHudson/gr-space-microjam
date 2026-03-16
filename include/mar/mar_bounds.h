#ifndef MAR_BOUNDS_H
#define MAR_BOUNDS_H

#include "bn_display.h"

// The bounds of the screen
static constexpr int MAX_X = bn::display::width() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_Y = -bn::display::height() / 2;

#endif