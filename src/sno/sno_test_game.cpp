#include "sno_test_game.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "mj/mj_game_list.h"

// String arrays for the credits can go in an anonymous namespace
namespace
{
    constexpr bn::string_view code_credits[] = {"Andrew Onjang & Mason Sabin"};
    constexpr bn::string_view graphics_credits[] = {"TBD..."};
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(sno::sno_test_game) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

// All game functions/classes/variables/constants scoped to the namespace
namespace sno
{
    sno_test_game::sno_test_game([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("sno"),
                                                                                                                     _player(sno::player({50, 30}, 2)),
                                                                                                                     _black_hole(sno::black_hole({0, 0}))
    {
    }

    bn::string<16> sno_test_game::title() const
    {
        return "Avoid the void!";
    }

    int sno_test_game::total_frames() const
    {
        return 600;
    }

    mj::game_result sno_test_game::play([[maybe_unused]] const mj::game_data &data)
    {
        _player.update();
        _player.attraction(_black_hole.position());
        mj::game_result result(victory(), false);
        return result;
    }

    bool sno_test_game::victory() const
    {
        return _player.out_of_bounds();
    }

    void sno_test_game::fade_in([[maybe_unused]] const mj::game_data &data)
    {
    }

    void sno_test_game::fade_out([[maybe_unused]] const mj::game_data &data)
    {
    }
}
