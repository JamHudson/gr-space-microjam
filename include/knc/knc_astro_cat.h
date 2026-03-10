#ifndef KNC_ASTRO_CAT_H
#define KNC_ASTRO_CAT_H

#include "mj/mj_game.h"
#include "knc/knc_cat.h"
#include "knc/knc_planet.h"

namespace knc {
    class knc_astro_cat : public mj::game {
    public:
        knc_astro_cat(int completed_games, const mj::game_data& data);

        bn::string<16> title() const override;
        int total_frames() const override;
        mj::game_result play(const mj::game_data& data) override;
        bool victory() const override;
        void fade_in(const mj::game_data& data) override;
        void fade_out(const mj::game_data& data) override;

    private:
        cat _cat;
        planet _planet;
        bool _hit;
    };
}

#endif