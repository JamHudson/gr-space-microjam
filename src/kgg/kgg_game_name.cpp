#include "bn_keypad.h"
#include "kgg/kgg_game_name.h"
#include "mj/mj_game_list.h"
#include "bn_display.h"
#include "bn_random.h"


namespace {
constexpr bn::string_view code_credits[] = { "Gurpinder Gill" };
constexpr bn::string_view graphics_credits[] = { "" };
constexpr bn::string_view music_credits[] = { "" };
constexpr bn::string_view sfx_credits[] = { "" };
}  

namespace kgg {

kgg_game_name::kgg_game_name([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data)
: mj::game("kgg")
{
}

bn::string<16> kgg_game_name::title() const
{
    return "move left right";
}

int kgg_game_name::total_frames() const
{
    return 600; // 10 seconds
}

mj::game_result kgg_game_name::play([[maybe_unused]] const mj::game_data& data)

{
    if(_game_over)
    {
        return mj::game_result();
    }

    // keeps player moving
    _player.update();

    // time increases by 1
    _spawn_timer++;

    if(_spawn_timer >= 30) // spawn a rock every half second
    {
        _spawn_timer = 0;

        if(_rocks.size() < _rocks.max_size())
        {
            static bn::random random;
            // chossing a random left right position at the top  
            int random_x = random.get_int(-bn::display::width() / 2 + 8,
                                          bn::display::width() / 2 - 8);

            // creates a rock high up, so it falls down into view                            
            _rocks.push_back(rock(random_x, -70));
        }
    }

    //rock moves downward every frame
    for(rock& r : _rocks)
    {
        r.update();

        // if rocks touch the player then game over
        if(r.collides_with(_player.x(), _player.y()))
        {
            _victory = false;
            _game_over = true;
        }
    }

    // if game is not over, then player win the game
    if(!_game_over)
    {
        _victory = true;
    }

    return mj::game_result();
}

bool kgg_game_name::victory() const
{
    //return false;
    return _victory;
}

void kgg_game_name::fade_in([[maybe_unused]] const mj::game_data& data)
{
}

void kgg_game_name::fade_out([[maybe_unused]] const mj::game_data& data)
{
}

}
MJ_GAME_LIST_ADD(kgg::kgg_game_name);

MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits);
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits);
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits);
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits); 

