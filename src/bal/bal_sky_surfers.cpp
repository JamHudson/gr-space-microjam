#include "bal_sky_surfers.h"
#include "mj/mj_game_list.h"

#include <bn_log.h>
#include "bn_regular_bg_items_stary_bg.h"
#include <bn_sprite_ptr.h>

namespace
{
    constexpr bn::string_view code_credits[] = { "Pasha", "Hosea" };
    constexpr bn::string_view graphics_credits[] = { "Hosea" };
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};

    constexpr bn::size ROCK_SIZE = {8, 8};
    constexpr int MIN_X = -bn::display::width() / 2;
    constexpr int MAX_X = bn::display::width() / 2;
    constexpr int MIN_Y = -bn::display::height() / 2;
}

MJ_GAME_LIST_ADD(bal::bal_sky_surfers)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace bal
{
bal_sky_surfers::bal_sky_surfers([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) :
    mj::game("bal"),
    _bal_player(player({0, 60}, 2)),
    _spawn_rocks(0),
    _rng(data.random),
    _player_intersects(false),
    _difficulty_level(_recommended_player_speed(recommended_difficulty_level(completed_games, data))),
    _background(bn::regular_bg_items::stary_bg.create_bg())

    {}


bn::string<16> bal_sky_surfers::title() const {
    return "Dodge the rocks";
}
bn::fixed bal_sky_surfers::_recommended_player_speed(mj::difficulty_level difficulty) {
    if(difficulty == mj::difficulty_level::EASY) {
        return 3;
    } else if (difficulty == mj::difficulty_level::NORMAL) {
        return 5;
    } 
    return 7;
}

int bal_sky_surfers::total_frames() const {
    return 600; // 600 frames at 60fps = 10 seconds
}

//spawns a rock at the top of the screen
void bal_sky_surfers::spawn_rock(){
    _spawn_rocks++;
    if(_spawn_rocks >= 60 && _rocks.size() < _rocks.max_size()){
        for(int i=0; i<3; i++){
            int rand_x = _rng.get_int(MIN_X, MAX_X);
            _rocks.push_back(rock(rand_x, MIN_Y, 2, ROCK_SIZE));
        }
        _spawn_rocks = 0;
    }
}

mj::game_result bal_sky_surfers::play([[maybe_unused]] const mj::game_data& data)
{
    mj::game_result result;

    _bal_player.update();

    for(int i=_difficulty_level; i>0; i--){
        spawn_rock();
    }

    for(int i = _rocks.size() - 1; i >= 0; i--){
        //checks if rocks are off the screen
        bool off_screen = _rocks[i].update();
        
        //checks if player got hit by a rock
        if(_rocks[i].bounding_box.intersects(_bal_player.bounding_box)){
            _player_intersects = true;
            result.exit = true;
            return result;
        }

        //removes the rock and puts it back at the start
        if(off_screen){
            _rocks.erase(_rocks.begin() + i);
        }
    }

return result;
}

bool bal_sky_surfers::victory() const {
    return !_player_intersects;
}

void bal_sky_surfers::fade_in([[maybe_unused]] const mj::game_data& data)
{
}

void bal_sky_surfers::fade_out([[maybe_unused]] const mj::game_data& data)
{
}

}