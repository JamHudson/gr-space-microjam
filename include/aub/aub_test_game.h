#ifndef AUB_TEST_GAME_H // Include guard must start with the 3-letter id
#define AUB_TEST_GAME_H

#include <bn_regular_bg_ptr.h>
#include <bn_sprite_ptr.h>

#include "mj/mj_game.h"
#include "aub/player.h"




// All game functions/classes/variables/constants scoped to the namespace
namespace aub
{

/**
 * aub_test_game is a class representing a microgame where the player must leave the screen.
 * 
 * Like all microgames, it is a public subclass of mj::game
 */
class aub_test_game : public mj::game
{
    public:
        /**
         * Constructor for an instance of an aub_test_game
         * 
         * @param completed_games how many microgames the player has completed so far
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        aub_test_game(int completed_games, const mj::game_data& data);

        /**
         * The instructions given to the player at the beginning of the microgame.
         * 
         * Must be <= 16 characters long
         */
        bn::string<16> title() const override;


        /**
         * How long the timer for the game should be set to in frames.
         * 
         * GBA runs at approx 60 frames per second.
         */
        int total_frames() const override;

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
        mj::game_result play(const mj::game_data& data) override;

        /**
         * Returns whether the player has won the microgame.
         * 
         * In this particular microgame the player wins if they make the ball leave the screen.
         */
        bool victory() const override;

        /**
         * Called repeatedly as the game fades into view. Unused for this particular microgame.
         * 
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        void fade_in(const mj::game_data& data) override;

        /**
         * Called repeatedly as the game fades into view. Unused for this particular microgame.
         * 
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        void fade_out(const mj::game_data& data) override;

    private:
        // The character that the player can move
        player _player;
        bn::regular_bg_ptr _background;

        // Returns progressively slower player speeds the harder the difficulty
        // The slower the player moves, the harder it is to leave the screen before the timer ends
        bn::fixed _recommended_player_speed(mj::difficulty_level difficulty);
};

}

#endif
