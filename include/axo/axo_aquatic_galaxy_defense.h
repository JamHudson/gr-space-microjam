#ifndef AXO_AQUATIC_GALAXY_DEFENSE_H
#define AXO_AQUATIC_GALAXY_DEFENSE_H

#include <bn_sprite_ptr.h>

#include "mj/mj_game.h"
#include "axo/axo_player.h"
#include "axo/axo_obstacle.h"
#include "axo/axo_hitbox.h"
#include "axo/axo_bubble.h"
#include "axo/axo_blast.h"
#include "bn_regular_bg_ptr.h"

namespace axo
{

class axo_aquatic_galaxy_defense : public mj::game
{
    public:
        /**
         * Constructor for an instance of an axo_aquatic_galaxy_defense game
         * 
         * @param completed_games how many microgames the player has completed so far
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        axo_aquatic_galaxy_defense(int completed_games, const mj::game_data& data);
       
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


         /** PLAY function. Repeats while game is active
         * @param data shared information, such as a rng and number of frames left in the microgame
         * @return the mj::game result indicating whether the game has finished and whether the title should be hidden
         */
        mj::game_result play(const mj::game_data& data) override;

        
        /**
         * Returns whether the player has won the microgame.
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

        // The obstacles in the game
        bn::vector<obstacle, 12> _obstacles = {};
        // The helper function that allows for obstacles to be destroyed
        void destroy_obstacle(int index);

        // Vector to store explosions!
        bn::vector<blast, 20> _blasts = {};

        // Returns progressively faster obstacle speeds the harder the difficulty
        bn::fixed _recommended_obstacle_speed(mj::difficulty_level difficulty);
};

}

#endif