#ifndef REB_BUZZ_GAME_H
#define REB_BUZZ_GAME_H

#include "bn_sprite_ptr.h"
#include "mj/mj_game.h"
#include "bn_sprite_items_reb_buzz.h"
#include "bn_sprite_items_reb_daisy.h"
#include "bn_sprite_animate_actions.h"
#include "bn_optional.h"

namespace reb
{

    class reb_buzz_game : public mj::game
    {
        public:

            static constexpr int minimum_frames = 3 * 60; 
            static constexpr int maximum_frames = 5 * 60; 

            reb_buzz_game(int completed_games, const mj::game_data& data);

            [[nodiscard]] bn::string<16> title() const final
            {
                return "Buzz Buzz";
            }

            [[nodiscard]] int total_frames() const final
            {
                return minimum_frames;
            }

            void fade_in(const mj::game_data& data) final;

            [[nodiscard]] mj::game_result play(const mj::game_data& data) final;

            [[nodiscard]] bool victory() const final;

            void fade_out(const mj::game_data& data) final;

        private:
            bn::sprite_ptr _playerSprite = bn::sprite_items::reb_buzz.create_sprite(0,0);
            bn::sprite_ptr _flowerSprite = bn::sprite_items::reb_daisy.create_sprite(-100,0);
            bn::optional<bn::sprite_animate_action<2>> _beeAnimation;
            bool _victory = false;
    };
}

#endif