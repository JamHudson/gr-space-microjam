#ifndef CAT_CAT_STELLAR_GAME_H
#define CAT_CAT_STELLAR_GAME_H

#include "mj/mj_game.h"
#include "bn_sprite_ptr.h"
#include "bn_optional.h"
#include "bn_array.h"
#include "cat/cat_player.h"
#include "bn_regular_bg_ptr.h"

namespace cat
{
    class cat_cat_stellar_game : public mj::game
    {
        public:
        /**
         * Constructor for an instance of a cat_stellar_game
         * 
         * @param completed_games how many microgames the player has completed so far
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        cat_cat_stellar_game(int completed_games, const mj::game_data& data);

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
         * In this particular microgame the player wins if they collect enough stars before time runs out.
         */
        bool victory() const override;

        /**
         * Called repeatedly as the game fades into view. Unused for this particular microgame.
         * 
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        void fade_in(const mj::game_data& data) override;

        /**
         * Called repeatedly as the game fades out of view. Unused for this particular microgame.
         * 
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        void fade_out(const mj::game_data& data) override;

    private:
        // The number of stars the player must collect to win
        static constexpr int _stars_to_win = 3;
        static constexpr int _total_stars = 5;
        static constexpr bn::fixed _collect_distance = 16;

        cat_player _player;
        bn::array<bn::optional<bn::sprite_ptr>, 5> _stars;
        int _stars_collected;

        void _check_collection();

        bn::regular_bg_ptr _background;
};
}

#endif // CAT_CAT_STELLAR_GAME_H