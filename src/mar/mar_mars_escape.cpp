#include "mar_mars_escape.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sound_items.h"
#include <bn_vector.h>

#include "mj/mj_game_list.h"
#include "mj/mj_game_data.h"
#include "bn_regular_bg_items_mar_bg.h"

// String arrays for the credits can go in an anonymous namespace
namespace
{
    constexpr bn::string_view code_credits[] = {"Buay Dak", "Samuel Marchuk"};
    constexpr bn::string_view graphics_credits[] = {"Buay Dak", "Samuel Marchuk"};
    constexpr bn::string_view sfx_credits[] = {"Person"};
    constexpr bn::string_view music_credits[] = {"vitalezzz"};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(mar::mar_mars_escape) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

// All game functions/classes/variables/constants scoped to the namespace
namespace mar
{

    /**
     * Constructor for an instance of an aub_test_game
     * @param completed_games how many microgames the player has completed so far
     * @param data shared information, such as a rng and number of frames left in the microgame
     */
    mar_mars_escape::mar_mars_escape([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("mar"),
                                                                                                                         _player(mar_player({MIN_X + 60, 0}, 2)),
                                                                                                                         _background(bn::regular_bg_items::mar_bg.create_bg())
    {
        // Sound for Background
        play_sound(bn::sound_items::mar_downfall, completed_games, data);

        bn::fixed diff = difficulty(recommended_difficulty_level(completed_games, data));

        for (int i = 0; i < 10 + diff * 5; i++)
        {
            enemies.push_back(mar_enemy(
                {data.random.get_int(MAX_X, MAX_X * 3),
                 data.random.get_int(MIN_Y, MAX_Y)},
                1 + diff));
            data.random.update();
        }
    }

    /**
     * Game title shown at the beginning of the microgame and brief description of game.
     * Must be <= 16 characters long
     */
    bn::string<16> mar_mars_escape::title() const
    {
        return "Escape Mars!";
    }

    /**
     * GBA runs at approx 60 frames per second.
     * Game last a maximum of 10 seconds, but can end early if the player collides with an enemy.
     */
    int mar_mars_escape::total_frames() const
    {
        return 600; // 600 frames at 60fps = 10 seconds
    }

    /**
     * play is repeatedly called while the microgame is playing.
     * @param data shared information, such as a rng and number of frames left in the microgame
     * @return the mj::game result indicating whether the game has finished and whether the title should be hidden
     */
    mj::game_result mar_mars_escape::play([[maybe_unused]] const mj::game_data &data)
    {
        // update the player position
        _player.update();

        // update the enemy positions and check for collisions
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].update();
            if (_player.rect().intersects(enemies[i].rect()))
            {
                collision = true;
                // if collision is true stop the game, keep title visible (false)
                return mj::game_result(true, false);
            }
            if (enemies[i].isPassed())
            {
                enemies[i].set_position(
                    {data.random.get_int(MAX_X, MAX_X * 2),
                     data.random.get_int(MIN_Y, MAX_Y)});
            }
        }
        // no collision keep the game running, keep title visible (false)
        return mj::game_result(false, false);
    }
    // true = player survived (no collision), false = player was hit (collision)
    bool mar_mars_escape::victory() const
    {
        return !collision;
    }

    /**
     * Called repeatedly as the game fades into view. Unused for this particular microgame.
     *
     * @param data shared information, such as a rng and number of frames left in the microgame
     */
    void mar_mars_escape::fade_in([[maybe_unused]] const mj::game_data &data)
    {
    }

    /**
     * Called repeatedly as the game fades into view. Unused for this particular microgame.
     *
     * @param data shared information, such as a rng and number of frames left in the microgame
     */
    void mar_mars_escape::fade_out([[maybe_unused]] const mj::game_data &data)
    {
    }

    bn::fixed mar_mars_escape::difficulty(mj::difficulty_level difficulty)
    {

        if (difficulty == mj::difficulty_level::EASY)
        {
            return 0;
        }
        else if (difficulty == mj::difficulty_level::NORMAL)
        {
            return 0.5;
        }
        return 1;
    }
}