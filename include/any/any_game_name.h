#ifndef ANY_GAME_NAME_H
#define ANY_GAME_NAME_H

#include <bn_sprite_ptr.h>
#include "bn_optional.h"
#include "bn_fixed.h"
#include "mj/mj_game.h"
#include "any_player.h"
#include "any_platform.h"
#include "bn_sprite_items_astronaut.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_animate_actions.h"


namespace any {

    class any_game_name : public mj::game {

        public:
        /**
         * Constructor for an instance of an any_test_game
         * 
         * @param completed_games how many microgames the player has completed so far
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        any_game_name(int completed_games, const mj::game_data& data);

    
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
     //the character that the player can move
     bn::optional<player> _player;
     bool _has_lost = false;
     bool _touched_moon() const;

     platform _platforms[3];

     static constexpr int _moon_x = 85; 

     bn::optional<bn::sprite_ptr> _moon_sprite;
     bn::optional<bn::sprite_animate_action<4>> _moon_anim;
     bn::fixed _moon_y = -60;
     bn::vector<bn::sprite_ptr, 8> _text_sprites;
     bn::optional<bn::regular_bg_ptr> _background;
     int _completed_games;
};

}

#endif


