#ifndef REB_ECLIPSE_GAME_H
#define REB_ECLIPSE_GAME_H

#include "bn_sprite_ptr.h"
#include "mj/mj_game.h"
#include "bn_sprite_items_reb_sun.h"
#include "bn_sprite_items_reb_moon.h"
#include "bn_sprite_items_reb_earth.h"
#include "bn_sprite_animate_actions.h"
#include "reb_moon.h"
#include "bn_optional.h"

namespace reb
{

    class reb_eclipse_game : public mj::game
    {
        public:

            static constexpr int game_length = 5 * 60; 

            reb_eclipse_game(int completed_games, const mj::game_data& data);

            [[nodiscard]] bn::string<16> title() const final
            {
                return "Solar Eclipse";
            }

            [[nodiscard]] int total_frames() const final
            {
                return game_length;
            }

            void fade_in(const mj::game_data& data) final;

            [[nodiscard]] mj::game_result play(const mj::game_data& data) final;

            [[nodiscard]] bool victory() const final;

            void fade_out(const mj::game_data& data) final;

        private:
            bn::sprite_ptr _sunSprite;
            bn::sprite_ptr _earthSprite;
            moon _moon;
            bn::sprite_animate_action<10> _sunAnimation;
            static constexpr bn::fixed _earth_x =  75;
            static constexpr bn::fixed _earth_y =   0;
            bool _victory;
    };
}

#endif