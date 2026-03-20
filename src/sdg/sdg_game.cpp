#include <bn_sprite_ptr.h>
#include <bn_sprite_animate_actions.h>
#include <bn_regular_bg_animate_actions.h>

#include "sdg_game.h"
#include "sdg/input.h"
#include "mj/mj_game_list.h"

//Graphics 
#include "bn_sprite_items_arrow_up.h"
#include "bn_sprite_items_arrow_right.h"
#include "bn_sprite_items_arrow_down.h"
#include "bn_sprite_items_arrow_left.h"
#include "bn_regular_bg_items_hyperdrivebg.h"

#include "bn_sound_items.h"

namespace
{
    constexpr bn::string_view code_credits[] = { "Iker", "Kevin James \"bigtoe\" Miclea" };
    constexpr bn::string_view graphics_credits[] = { "Kevin James \"bigtoe\" Miclea" };
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(sdg::sdg_game) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace sdg{
    sdg_game::sdg_game([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) :
    mj::game("sdg"),
        _player(input(_code_difficulty(recommended_difficulty_level(completed_games, data)), data.random)),
        _background(bn::regular_bg_items::hyperdrivebg.create_bg(8, 48))
    {

        play_sound(bn::sound_items::sdg_game_music, completed_games, data);
        
        // Get the randomly generated arrow pattern from the input system.
        const auto& pattern = _player.challenge();

        // Initial x positon.
        int start_x = -95;

        // Starting y position.
        int y = -40;

        // This array maps each number in the pattern to a specific sprite type.
        const bn::sprite_item* arrow_items[4] = {
            &bn::sprite_items::arrow_up,
            &bn::sprite_items::arrow_right,
            &bn::sprite_items::arrow_down,
            &bn::sprite_items::arrow_left
        };

        // pattern.size() tells us how many arrows the player must input. So basically the difficulty
        for(int i = 0; i < pattern.size(); ++i)
        {
            // Each x-coordinate is spaced 20px aprt. 
            // This needs to change because in hard difficulty the pattern doesnt fit on the screen
            int x = start_x + (i * 20);

            // pattern[i] returns a number from 0–3, that number says which sprite item to use from arrow_items.
            bn::sprite_ptr sprite =
                arrow_items[pattern[i]]->create_sprite(x, y);

            // Store the created sprite inside the _arrows vector.
            // bn::move transfers ownership of the sprite into the vector instead of copying it
            _arrows.push_back(bn::move(sprite));
        }
    }

    bn::string<16> sdg_game::title() const {
    return "Enter the code!";
    }

    int sdg_game::total_frames() const {
        return 300; // 5 seconds
    }

    mj::game_result sdg_game::play([[maybe_unused]] const mj::game_data& data)
    {
        _player.update();

        // player progress class attribute
        int progress = _player.progress();

        // initialize arrows
        const bn::sprite_item* arrow_items[4] = {
            &bn::sprite_items::arrow_up,
            &bn::sprite_items::arrow_right,
            &bn::sprite_items::arrow_down,
            &bn::sprite_items::arrow_left
        };

        // arrow pattern (pointer)
        const auto& pattern = _player.challenge();

        // shows green arrows when correct
        for(int i = 0; i < progress; ++i)
        {
            _arrows[i].set_tiles(
                arrow_items[pattern[i]]->tiles_item().create_tiles(1)
            );
        }

        // resets arrows when incorrect, with some angry flair
        if (_player.incorrect_input) {
            bn::sound_items::sdg_incorrectsfx.play();
            for (int i = 0; i < _player.challenge().size(); i++) {
                _arrows[i].set_tiles(arrow_items[pattern[i]]->tiles_item(), 2);
            }
            _player.incorrect_input = false;
        }

        if (_player.correct_input) {
            bn::sound_items::sdg_correctsfx.play();
            _player.correct_input = false;
        }

        mj::game_result result(victory(), false);
        return result;
    }

    bool sdg_game::victory() const {
        return _player.code_is_correct();
    }

    void sdg_game::fade_in([[maybe_unused]] const mj::game_data& data)
    {
    }

    void sdg_game::fade_out([[maybe_unused]] const mj::game_data& data)
    {
    }

    int sdg_game::_code_difficulty(mj::difficulty_level diff) {
        if (diff == mj::difficulty_level::EASY) {
            return 5;
        } else if (diff == mj::difficulty_level::NORMAL) {
            return 7;
        } else {
            return 10;
        }
    }
}