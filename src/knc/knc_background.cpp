#include "knc/knc_background.h"
#include "bn_regular_bg_items_space_bg.h"

namespace knc {

background::background() :
    _bg(bn::regular_bg_items::space_bg.create_bg(0, 0)),
    _scroll_y(0)
{
    _bg.set_priority(3);
}

void background::update()
{
    // move downward to match the fire planet
    _scroll_y += bn::fixed(0.5);
    _bg.set_position(0, _scroll_y);
}

} // namespace knc