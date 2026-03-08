#include "axo_aquatic_galaxy_defense.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

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
        _player(player({20, 0}, 2, PLAYER_SIZE))
        {}

/**
 * The instructions given to the player at the beginning of the microgame.
 * 
 * Must be <= 16 characters long
 */
bn::string<16> axo_aquatic_galaxy_defense::title() const {
    return "Survive!";
}

/**
 * How long the timer for the game should be set to in frames.
 * 
 * GBA runs at approx 60 frames per second.
 */
int axo_aquatic_galaxy_defense::total_frames() const {
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
mj::game_result axo_aquatic_galaxy_defense::play([[maybe_unused]] const mj::game_data& data)
{
    // update the player position
    _player.update();

    // Creates a game result indicating whether the game is finished and whether the title should be hidden early
    // For this game the game should end early if the player has won (if victory returns true)
    // The title is not hidden early (false is passed), so the title disappears at the default time
    mj::game_result result(victory(), false);
    return result;
}

/**
 * Returns whether the player has won the microgame.
 * 
 * In this particular microgame the player wins if they make the ball leave the screen.
 */
bool axo_aquatic_galaxy_defense::victory() const {
    return _player.still_alive();
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
}

}