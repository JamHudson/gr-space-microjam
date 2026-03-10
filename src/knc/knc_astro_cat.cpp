#include "knc/knc_astro_cat.h"
#include "mj/mj_game_list.h"
namespace {
    constexpr bn::string_view code_credits[] = { "knc" };
    constexpr bn::string_view graphics_credits[] = { "knc" };
    constexpr bn::string_view sfx_credits[] = { "" };
    constexpr bn::string_view music_credits[] = { "" };
}

namespace knc {

    knc_astro_cat::knc_astro_cat(int completed_games, const mj::game_data& data)
        : mj::game("knc"),
        // start in middle, speed number 2
        _cat(bn::fixed_point(0,0), 2),
        _planet(bn::fixed_point(0, -80), 2),
        _hit(false)
    {}

    bn::string<16> knc_astro_cat::title() const
    {
        return "Dodge Them Fire!";
    }

    int knc_astro_cat::total_frames() const
    {
        return 60 * 5; 
    }

    mj::game_result knc_astro_cat::play(const mj::game_data& data)
    {
        _cat.update();

        _planet.update();
        if(_planet.off_screen()) {
            bn::fixed x = bn::fixed(data.random.get_int(200)) - 100;
            _planet = planet(bn::fixed_point(x, -80), 2);
        }
        // if planet hit cat, end game 
        if (_planet.collides_with(_cat.position(), cat::COLLISION_RADIUS)) {
            _hit = true;
        }
        return mj::game_result(_hit, false);
    }

    bool knc_astro_cat::victory() const
    {
        return !_hit;
    }

    void knc_astro_cat::fade_in(const mj::game_data&)
    {
    }

    void knc_astro_cat::fade_out(const mj::game_data&)
    {
    }

} // namespace knc

MJ_GAME_LIST_ADD(knc::knc_astro_cat)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)