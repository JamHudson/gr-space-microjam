#include "reb_eclipse_game.h"

#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "mj/mj_game_list.h"

namespace
{
    constexpr bn::string_view code_credits[] = { "Rebecca Riffle" };
    constexpr bn::string_view graphics_credits[] = { "Rebecca Riffle" };
    constexpr bn::string_view sfx_credits[] = {""};
}

MJ_GAME_LIST_ADD(reb::reb_eclipse_game)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace reb
{
    static constexpr int sun_x = -105; 
    static constexpr int sun_y = -0; 
    static constexpr int moon_x_init = 28; 
    static constexpr int moon_y_init = 270; 

    reb_eclipse_game::reb_eclipse_game([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) :
        mj::game("reb"),
        _sunSprite(bn::sprite_items::reb_sun.create_sprite(sun_x,sun_y)),
        _earthSprite(bn::sprite_items::reb_earth.create_sprite(_earth_x,_earth_y)),
        _moon(_earth_x, _earth_y, moon_x_init, moon_y_init), // start above earth
        _sunAnimation(bn::create_sprite_animate_action_forever(_sunSprite, 6, bn::sprite_items::reb_sun.tiles_item(), 0, 1, 2, 3, 4, 5, 6, 7, 8, 9)),
        _victory(false)
    {
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
        return _victory;
    }

    void reb_eclipse_game::fade_out([[maybe_unused]] const mj::game_data& data)
    {
    }

}