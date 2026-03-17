// Include guard 
#ifndef SDG_GAME_H 
#define SDG_GAME_H

#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_regular_bg_ptr.h>

#include "mj/mj_game.h"
#include "sdg/input.h"

namespace sdg{
    class sdg_game : public mj::game {
    public:
    // Constructor
    sdg_game(int completed_games, const mj::game_data& data);

    // Required overrides
    bn::string<16> title() const override;

    int total_frames() const override;

    mj::game_result play(const mj::game_data& data) override;

    // returns true if the code entered is correct
    bool victory() const override;

    
    void fade_in(const mj::game_data& data) override;

    
    void fade_out(const mj::game_data& data) override;

    private:
        // An instance of the players capability to input
        input _player;

        bn::vector<bn::sprite_ptr, 10> _arrows;

        // Returns an array size that gradually increases, making codes longer
        // and therefore more difficult.
        int _code_difficulty(mj::difficulty_level difficulty);

        // Game background.
        bn::regular_bg_ptr _background;
}; 
}

#endif