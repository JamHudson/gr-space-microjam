#include "bn_keypad.h"
#include "kgg/kgg_game_name.h"
#include "mj/mj_game_list.h"
#include "bn_display.h"
#include "bn_random.h"
#include "bn_regular_bg_items_kgg_background.h"

#include "bn_sound_items.h" 

 


namespace {
constexpr bn::string_view code_credits[] = { "Gurpinder Gill" };
constexpr bn::string_view graphics_credits[] = { "" };
constexpr bn::string_view music_credits[] = { "" };
constexpr bn::string_view sfx_credits[] = { "" };
}  

namespace kgg {

bn::fixed kgg_game_name::_speed(mj::difficulty_level difficulty)
{
    if(difficulty == mj::difficulty_level::EASY)
    {
        return 1.5;
    }
    else if(difficulty == mj::difficulty_level::NORMAL)
    {
        return 2.5;
    }
    return 4.0;
}

kgg_game_name::kgg_game_name(int completed_games, const mj::game_data& data)
: mj::game("kgg"),
  _data(data),
  _background(bn::regular_bg_items::kgg_background.create_bg())
{
    _rock_speed = _speed(recommended_difficulty_level(completed_games, data));

    // boss music for this game
    play_sound(bn::sound_items::kgg_boss, completed_games, data); 
    

}


bn::string<16> kgg_game_name::title() const
{
    return "Avoid the Rocks";
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

   if(_spawn_timer >= _spawn_limit) // spawn a rock every half second
    {
        _spawn_timer = 0;

        if(_rocks.size() < _rocks.max_size())
        {
            bn::random& random = _data.random;
            int random_x = random.get_int(-bn::display::width() / 2 + 8,
                                        bn::display::width() / 2 - 8);

            // creates a rock high up, so it falls down into view                            
            _rocks.push_back(rock(random_x, -70, _rock_speed));

        }
    }

    //rock moves downward every frame
    for(rock& r : _rocks)
    {
        r.update();

        // if rocks touch the player then game over
        if(r.collides_with(_player.x(), _player.y()))
        {
            // play a bomb sound during the game when u hit rock
            bn::sound_items::kgg_bomb.play();
            _victory = false;
            _game_over = true;
            return mj::game_result{ true, true };
        }
    }

    // if game is not over, then player win the game
    if(!_game_over)
    {
        _victory = true;
        _score++;   // increase score every frame survived

        // update score text
        _score_sprites.clear();

        bn::string<32> score_text = "Score: ";
        score_text.append(bn::to_string<16>(_score));

        _data.text_generator.generate(-100, -70, score_text, _score_sprites);
    }

    return mj::game_result();
}

bool kgg_game_name::victory() const
{
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

