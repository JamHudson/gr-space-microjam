#ifndef BAL_SKY_SURFERS_H
#define BAL_SKY_SURFERS_H

#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_random.h>

#include "mj/mj_game.h"
#include "bal/bal_player.h"
#include "bal/bal_rocks.h"

namespace bal
{
    class bal_sky_surfers : public mj::game
    {
    public:
        bal_sky_surfers(int completed_games, const mj::game_data& data);

        bn::string<16> title() const override;

        int total_frames() const override;

        mj::game_result play(const mj::game_data& data) override;

        bool victory() const override;

        void fade_in(const mj::game_data& data) override;

        void fade_out(const mj::game_data& data) override;
    private:
        player _bal_player;
        bn::vector<rock, 50> _rocks;
        int _spawn_rocks;
        bn::random& _rng;
        bool _player_intersects;
        int _difficulty_level;
        void spawn_rock();
        int _recommended_player_speed(mj::difficulty_level difficulty);
};

}

#endif