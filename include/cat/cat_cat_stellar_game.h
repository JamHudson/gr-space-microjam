#ifndef CAT_CAT_STELLAR_GAME_H
#define CAT_CAT_STELLAR_GAME_H

#include "mj/mj_game.h"
#include "bn_sprite_ptr.h"
#include "bn_optional.h"
#include "bn_array.h"
#include "cat/cat_player.h"
#include "cat/cat_enemy.h"
#include "cat/cat_star.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_vector.h"

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
        static constexpr int _total_stars = 10;
        static constexpr bn::fixed _collect_distance = 16;
        
        int _completed_games; 
        
        mj::difficulty_level _difficulty;
        int _stars_to_win;

        cat_player _player;
        cat_enemy _enemy;

        bn::array<bn::optional<cat::star>, _total_stars> _stars;
        int _stars_collected;
        bool _lost;
       
        const bn::sprite_text_generator& _text_generator;
        bn::vector<bn::sprite_ptr, 16> _score_sprites;

        void _check_collection(const mj::game_data& data);
        void _update_score_display();

        
        bn::regular_bg_ptr _background;

        //helper functions
        static bn::fixed _recommended_player_speed(mj::difficulty_level difficulty);
        static int _recommended_stars_to_win(mj::difficulty_level difficulty);
        static bn::fixed _recommended_enemy_speed(mj::difficulty_level difficulty);
        static bn::fixed_point _recommended_enemy_start_position(mj::difficulty_level difficulty);
    };
}

#endif // CAT_CAT_STELLAR_GAME_H