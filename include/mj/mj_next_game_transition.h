#ifndef MJ_NEXT_GAME_TRANSITION_H
#define MJ_NEXT_GAME_TRANSITION_H

#include "bn_rect_window_boundaries_hbe_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace mj
{

class next_game_transition
{

public:
    explicit next_game_transition(int completed_games);

    [[nodiscard]] bool update();

private:
    int _completed_games;
};

}

#endif
