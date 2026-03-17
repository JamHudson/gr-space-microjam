#include "axo_aquatic_galaxy_defense.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include <bn_vector.h>

#include "mj/mj_game_list.h"

// String arrays for the credits can go in an anonymous namespace
namespace
{
    constexpr bn::string_view code_credits[] = { "Jaronie", "Galatear" };
    constexpr bn::string_view graphics_credits[] = { "Galatear", "Jaronie" };
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(axo::axo_aquatic_galaxy_defense) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

// All game functions/classes/variables/constants scoped to the namespace
namespace axo
{

/**
 * Constructor for an instance of an axo_aquatic_galaxy_defense
 * 
 * First item in the initializer list MUST be a call to the superclass, mj::game with the identifier for the microgame.
 * 
 * @param completed_games how many microgames the player has completed so far
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
axo_aquatic_galaxy_defense::axo_aquatic_galaxy_defense([[maybe_unused]] int completed_games, 
    [[maybe_unused]] const mj::game_data& data) :
        mj::game("axo"),
        _player(player({0, 20}, 
        _recommended_player_speed(recommended_difficulty_level(completed_games, data)), 
        PLAYER_SIZE)),
        _obstacles()
        {
            //spawn 10 obstacles, top of screen with varying x values
            for(int i = 0; i < 10; i++) {
                _obstacles.push_back(obstacle(-bn::display::width() / 2 + 20 + (i * 30), 
                -bn::display::height(), 1, OBSTACLE_SIZE));
            }
        }

/**
 * The instructions given to the player at the beginning of the microgame.
 * 
 * Must be <= 16 characters long
 */
bn::string<16> axo_aquatic_galaxy_defense::title() const {
    return "Shoot the rocks!";
}

/**
 * How long the timer for the game should be set to in frames.
 * 
 * GBA runs at approx 60 frames per second.
 */
int axo_aquatic_galaxy_defense::total_frames() const {
    return 300; // 300 frames at 60fps = 5 seconds
}

void axo_aquatic_galaxy_defense::destroy_obstacle(int index) {
    _obstacles.erase(_obstacles.begin() + index);
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
mj::game_result axo_aquatic_galaxy_defense::play([[maybe_unused]] const mj::game_data& data)
{
    // update the player position
    _player.update();

    for(int b = 0; b < _player.bubbles_size(); ++b) {
        for(int i = 0; i < _obstacles.size(); ++i) {
            auto& bubble = _player.get_bubble(b);
            auto& obstacle = _obstacles[i];
            if(bubble.get_hitbox().intersects(obstacle.get_hitbox())) {
                destroy_obstacle(i);
                break;
            }
        }
    }

    for(auto& obstacle : _obstacles) {
        obstacle.update(_player);
        if(_player.get_hitbox().intersects(obstacle.get_hitbox())) {
            _player.kill();
        }
    }

    if(!_player.alive()) {
        _player.clear_bubbles();
        return mj::game_result(true, true);
    }

    mj::game_result result(false, false);
    return result;
}

/**
 * Returns whether the player has won the microgame.
 * 
 * In this particular microgame the player wins if they survive for the whole duration.
 */
bool axo_aquatic_galaxy_defense::victory() const {
    return _player.alive();
}

/**
 * Called repeatedly as the game fades into view. Unused for this particular microgame.
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
void axo_aquatic_galaxy_defense::fade_in([[maybe_unused]] const mj::game_data& data)
{
}

/**
 * Called repeatedly as the game fades into view. Unused for this particular microgame.
 * 
 * @param data shared information, such as a rng and number of frames left in the microgame
 */
void axo_aquatic_galaxy_defense::fade_out([[maybe_unused]] const mj::game_data& data)
{
    _player.clear_bubbles();
}

bn::fixed axo_aquatic_galaxy_defense::_recommended_player_speed(mj::difficulty_level difficulty) {
    if(difficulty == mj::difficulty_level::EASY) {
        return 1;
    } else if (difficulty == mj::difficulty_level::NORMAL) {
        return .5;
    } 
    return .3;
}

}