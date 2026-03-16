#include "cat/cat_cat_stellar_game.h"

#include "mj/mj_game_list.h"
#include "bn_sprite_items_cat_star.h"
#include "bn_sprite_items_cat_enemy.h"
#include "bn_regular_bg_items_cat_background.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_font.h"
#include "mj/mj_small_sprite_font.h"
#include "bn_vector.h"
#include "bn_string.h"

//anonymous namespace 
namespace
{
    constexpr bn::string_view code_credits[] = { "Nadia Ivanishchuk", "Paris Allkurti" };
    constexpr bn::string_view graphics_credits[] = { "Paris Allkurti", "Nadia Ivanishchuk" };
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

// All game functions/classes/variables/constants scoped to the namespace
namespace cat
{
/**
 * Constructor for an instance of a cat_stellar_game
 * 
 * First item in the initializer list MUST be a call to the superclass, mj::game with the identifier for the microgame.
 * 
 * @param completed_games how many microgames the player has completed so far
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
cat_cat_stellar_game::cat_cat_stellar_game([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) :
    mj::game("cat"),
    _difficulty(recommended_difficulty_level(completed_games, data)),
    _stars_to_win(_recommended_stars_to_win(_difficulty)),
    _player({0, 0}, _recommended_player_speed(_difficulty)),
    _enemy(_recommended_enemy_start_position(_difficulty).x(), 
           _recommended_enemy_start_position(_difficulty).y(), 
           _recommended_enemy_speed(_difficulty)),
    _stars_collected(0),
    _lost(false),
    _text_generator(data.text_generator),
    _background(bn::regular_bg_items::cat_background.create_bg(0, 0))
{
    for(int i = 0; i < _total_stars; ++i) {
        bn::fixed x = bn::fixed(data.random.get_int(200)) - 100; 
        bn::fixed y = bn::fixed(data.random.get_int(120)) - 60; 
        _stars[i] = bn::sprite_items::cat_star.create_sprite({x, y});
    }
    _update_score_display();
}

bn::fixed cat_cat_stellar_game::_recommended_player_speed(mj::difficulty_level difficulty)
{
    switch(difficulty)
    {
        case mj::difficulty_level::EASY:
            return 2.5;
        case mj::difficulty_level::NORMAL:
            return 2.0;
        case mj::difficulty_level::HARD:
            return 1.5;
        default:
            return 2.0;
    }
}

int cat_cat_stellar_game::_recommended_stars_to_win(mj::difficulty_level difficulty)
{
    switch(difficulty)
    {
        case mj::difficulty_level::EASY:
            return 3;
        case mj::difficulty_level::NORMAL:
            return 5;
        case mj::difficulty_level::HARD:
            return 7;
        default:
            return 3;
    }
}

bn::fixed cat_cat_stellar_game::_recommended_enemy_speed(mj::difficulty_level difficulty)
{
    switch(difficulty)
    {
        case mj::difficulty_level::EASY:
            return 0.4;
        case mj::difficulty_level::NORMAL:
            return 0.6;
        case mj::difficulty_level::HARD:
            return 0.8;
        default:
            return 0.6;
    }
}

bn::fixed_point cat_cat_stellar_game::_recommended_enemy_start_position(mj::difficulty_level difficulty)
{
    switch(difficulty)
    {
        case mj::difficulty_level::EASY:
            return {100, 60};  // Far from player (0, 0)
        case mj::difficulty_level::NORMAL:
            return {80, 50};   // Medium distance
        case mj::difficulty_level::HARD:
            return {60, 40};   // Closer
        default:
            return {100, 60};
    }
}

/**
 * The instructions given to the player at the beginning of the microgame.
 * 
 * Must be <= 16 characters long
 */
bn::string<16> cat_cat_stellar_game::title() const {
    return "Collect Stars";
}

/**
 * How long the timer for the game should be set to in frames.
 * 
 * GBA runs at approx 60 frames per second.
 */
int cat_cat_stellar_game::total_frames() const {
    return 300; // 300 frames at 60fps = 5 seconds
}

/**
 * play is repeatedly called while the microgame is playing.
 * 
 * You can think of it as what previously was in the while event loop.
 * You do NOT need to write your own while event loop
 * You do NOT need to call bn::core::update()
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 * @return the mj::game result indicating whether the game has finished and whether the title should be hidden
 */
mj::game_result cat_cat_stellar_game::play([[maybe_unused]] const mj::game_data& data)
{
    _player.update();
    _enemy.update(_player.position());
    _check_collection();

    if(_enemy.collides_with(_player.position()))
    {
        _lost = true;
        return { true, false };
    }

    return { victory(), false};
}

/**
 * Returns whether the player has won the microgame.
 * 
 * In this particular microgame the player wins if they collect enough stars before time runs out.
 */
bool cat_cat_stellar_game::victory() const {
    if(_lost)
    {
        return false;
    }
    return _stars_collected >= _stars_to_win;
}

/**
 * Checks if the player has collected any stars and updates the score accordingly.
 */
void cat_cat_stellar_game::_check_collection()
{
    bn::fixed_point player_pos = _player.position();

    for(auto& star : _stars)
    {
        if(star.has_value())
        {
            bn::fixed dx = player_pos.x() - star->x();
            bn::fixed dy = player_pos.y() - star->y();
            // squared distance avoids needing sqrt
            bn::fixed dist_sq = (dx * dx) + (dy * dy);

            if(dist_sq < _collect_distance * _collect_distance)
            {
                star.reset(); // hides the sprite and frees it
                _stars_collected++;
                _update_score_display();
            }
        }
    }
}

/**
 * Updates the score display to show progress (e.g., "3/5 Stars")
 */
void cat_cat_stellar_game::_update_score_display()
{
    _score_sprites.clear();

    bn::string<20> score_text = bn::to_string<2>(_stars_collected);
    score_text.append("/");
    score_text.append(bn::to_string<2>(_stars_to_win));
    score_text.append(" Stars");
    
    _text_generator.generate(-90, -70, score_text, _score_sprites);
}

/**
 * Called repeatedly as the game fades into view. Unused for this particular microgame.
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
void cat_cat_stellar_game::fade_in([[maybe_unused]] const mj::game_data& data)
{
}

/**
 * Called repeatedly as the game fades out of view. Unused for this particular microgame.
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
void cat_cat_stellar_game::fade_out([[maybe_unused]] const mj::game_data& data)
{
}

}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(cat::cat_cat_stellar_game) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)