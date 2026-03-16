#include "sno/sno_test_game.h"
#include "sno/black_hole.h"
#include "sno/sno_player.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "mj/mj_game_list.h"

// String arrays for the credits can go in an anonymous namespace
namespace
{
    constexpr bn::string_view code_credits[] = {"Andrew Onjang & Mason Sabin"};
    constexpr bn::string_view graphics_credits[] = {"Mason Sabin"};
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
                                                                                                                     _player(sno::player({50, 30}, _recommended_player_speed(recommended_difficulty_level(completed_games, data)))),
                                                                                                                     _black_hole(sno::black_hole({0, 0}))
    {
    }

    bn::string<16> sno_test_game::title() const
    {
        return "Avoid the void!";
    }

// Returns a stronger black hole attraction the harder the difficulty
    bn::fixed sno_test_game::_recommended_player_speed(mj::difficulty_level difficulty) {
        if(difficulty == mj::difficulty_level::EASY) {
            return 2;
        } else if(difficulty == mj::difficulty_level::NORMAL) {
            return 1.5;
        } 
        return 1;
    }


    int sno_test_game::total_frames() const
    {
        return 600;
    }

    mj::game_result sno_test_game::play([[maybe_unused]] const mj::game_data &data)
    {
        _player.update();
        _player.attraction(_black_hole.position());

        // Check if player collides with black hole
        if (_player.collides_with(_black_hole.position(), 8))
        {
            _player_captured = true;
        }

        mj::game_result result(_player_captured, false);
        return result;
    }

    bool sno_test_game::victory() const
    {
        // Player wins by surviving (staying out of the black hole)
        // Player loses if captured - returning false here means they lose
        return !_player_captured;
    }

    void sno_test_game::fade_in([[maybe_unused]] const mj::game_data &data)
    {
    }

    void sno_test_game::fade_out([[maybe_unused]] const mj::game_data &data)
    {
    }
}
