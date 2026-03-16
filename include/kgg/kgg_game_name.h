#ifndef KGG_GAME_NAME_H
#define KGG_GAME_NAME_H

#include "mj/mj_game.h"
#include "kgg/kgg_player.h"

namespace kgg {

class kgg_game_name : public mj::game
{

public:

    kgg_game_name(int completed_games, const mj::game_data& data);

    bn::string<16> title() const override;

    int total_frames() const override;

    mj::game_result play(const mj::game_data& data) override;

    bool victory() const override;

    void fade_in(const mj::game_data& data) override;

    void fade_out(const mj::game_data& data) override;

private:
    bool _victory = false;
    player _player;


};

}

#endif