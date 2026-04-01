#include "reb_eclipse_game.h"

#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "mj/mj_game_list.h"
#include "bn_regular_bg_items_reb_space.h"
#include "bn_sound_items.h"

namespace
{
    constexpr bn::string_view code_credits[] = { "Rebecca Riffle" };
    constexpr bn::string_view graphics_credits[] = { "Rebecca Riffle" };
    constexpr bn::string_view music_credits[] = {"Centurion_of_war"};
    constexpr bn::string_view sfx_credits[] = {"aquinn"};
}

MJ_GAME_LIST_ADD(reb::reb_eclipse_game)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace reb
{
    static constexpr bn::fixed sun_x = -105; 
    static constexpr bn::fixed sun_y = 0; 
    static constexpr bn::fixed moon_x_init = 28; 
    static constexpr bn::fixed moon_y_init = 270;
    static constexpr bn::fixed human_error_allowed = 150; // reduce to make game more difficult, increase to make game more lenient

    bool solar_eclipse_check(bn::fixed, bn::fixed, bn::fixed, bn::fixed);

    reb_eclipse_game::reb_eclipse_game([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) :
        mj::game("reb"),
        _background(bn::regular_bg_items::reb_space.create_bg()),
        _sunSprite(bn::sprite_items::reb_sun.create_sprite(sun_x,sun_y)),
        _earthSprite(bn::sprite_items::reb_earth.create_sprite(_earth_x,_earth_y)),
        _moon(_earth_x, _earth_y, moon_x_init, moon_y_init, _recommended_moon_speed(recommended_difficulty_level(completed_games, data))), // start above earth
        _sunAnimation(bn::create_sprite_animate_action_forever(_sunSprite, 6, bn::sprite_items::reb_sun.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8, 9)),
        _victory(false)
    {
        play_sound(bn::sound_items::reb_no_stars, completed_games, data);
    }

    bn::fixed reb_eclipse_game::_recommended_moon_speed(mj::difficulty_level difficulty) {
        if(difficulty == mj::difficulty_level::EASY) {
            return 2;
        } else if (difficulty == mj::difficulty_level::NORMAL) {
            return 1;
        } 
        return .5;
    }

    void reb_eclipse_game::fade_in([[maybe_unused]] const mj::game_data& data)
    {
    }

    mj::game_result reb_eclipse_game::play([[maybe_unused]] const mj::game_data& data)
    {
        _moon.update();
        _sunAnimation.update();

        mj::game_result result(victory(), false);

        return result;
    }

    bool reb_eclipse_game::victory() const
    {
        // logic to check is earth is between sun and moon
        return (solar_eclipse_check(_moon.x(), _moon.y(), _earth_x, _earth_y));
    }

    void reb_eclipse_game::fade_out([[maybe_unused]] const mj::game_data& data)
    {
    }

    bool solar_eclipse_check(bn::fixed curr_moon_x, bn::fixed curr_moon_y, bn::fixed curr_earth_x, bn::fixed curr_earth_y)
    {
        // check if all three are in line
        bn::fixed in_line = (curr_earth_x - sun_x) * (curr_moon_y - sun_y) - (curr_earth_y - sun_y) * (curr_moon_x - sun_x);
        if (in_line < 0) { in_line *= -1; } // handle large negative numbers
        if (in_line > human_error_allowed) return false;

        // check the moon if the moon is in the middle
        if (curr_earth_x < curr_moon_x) return false;

        return true;
    }
}