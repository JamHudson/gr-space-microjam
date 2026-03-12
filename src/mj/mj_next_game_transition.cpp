#include "mj/mj_next_game_transition.h"

#include "bn_sprite_palette_ptr.h"
#include "bn_sprite_affine_mat_ptr.h"

#include "bn_sprite_items_mj_big_digits.h"

namespace mj
{



next_game_transition::next_game_transition(int completed_games) :
    _completed_games(completed_games)
{
}

bool next_game_transition::update()
{
    // TODO: Show transition animation / game count
    return false;
}


}
