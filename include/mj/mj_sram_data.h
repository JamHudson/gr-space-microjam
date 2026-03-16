#ifndef MJ_SRAM_DATA_H
#define MJ_SRAM_DATA_H

#include "bn_span.h"

namespace mj
{

class sram_data
{

public:
    void init();

    [[nodiscard]] bool allow_intro_skip() const
    {
        return _allow_intro_skip;
    }

    void set_allow_intro_skip(bool allow)
    {
        _allow_intro_skip = allow;
    }

    [[nodiscard]] int intro_index() const
    {
        return _intro_index;
    }

    void set_intro_index(int intro_index)
    {
        _intro_index = intro_index;
    }

    [[nodiscard]] bn::span<const int> high_scores() const
    {
        return _high_scores;
    }

    void add_high_score(int high_score);

    void set_chosen_game(int game_index) {
        _chosen_game = game_index;
    }

    [[nodiscard]] int chosen_game() const {
        return _chosen_game;
    }

    void write();

private:
    char _label[8] = {};
    int _high_scores[3] = {};
    int _intro_index = 0;
    bool _allow_intro_skip = false;
    int _chosen_game = -1; // TODO: Use title?
};

}

#endif
