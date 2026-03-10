#include "cat/cat_cat_stellar_game.h"

#include "mj/mj_game_list.h"

#include "bn_sprite_items_cat_star.h"
#include "bn_regular_bg_items_cat_background.h"


// add an anonymous namespace after your includes but before 
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
    _player({0, 0}, 2),
    _stars_collected(0),
    _background(bn::regular_bg_items::cat_background.create_bg(0, 0))
    {
        for(int i = 0; i < _total_stars; ++i) {
            bn::fixed x = bn::fixed(data.random.get_int(200)) - 100; // Random x between -100 and 100
            bn::fixed y = bn::fixed(data.random.get_int(120)) - 60; // Random y between -60 and 60
            _stars[i] = bn::sprite_items::cat_star.create_sprite({x, y});
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
    _check_collection();
    return { victory(), false};
}

/**
 * Returns whether the player has won the microgame.
 * 
 * In this particular microgame the player wins if they collect enough stars before time runs out.
 */
bool cat_cat_stellar_game::victory() const {
    return _stars_collected >= _stars_to_win;
}

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
            }
        }
    }
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