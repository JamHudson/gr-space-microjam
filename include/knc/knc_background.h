#ifndef KNC_BACKGROUND_H
#define KNC_BACKGROUND_H

#include "bn_regular_bg_ptr.h"
#include "bn_fixed.h"

namespace knc {

// Scrolling space background
class background {
public:
    background();
    void update();

private:
    bn::regular_bg_ptr _bg;
    bn::fixed          _scroll_y;
};

} // namespace knc

#endif