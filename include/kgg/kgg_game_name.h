#ifndef KGG_GAME_NAME_H
#define KGG_GAME_NAME_H

#include "bn_sprite_ptr.h"
#include "mj/mj_game.h"
#include "bn_vector.h"
#include "kgg/kgg_rock.h"
#include "kgg/kgg_player.h"
#include "bn_regular_bg_ptr.h"


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

    bn::fixed _rock_speed = 3.5;
    bn::fixed _speed(mj::difficulty_level difficulty);
    int _spawn_limit = 50;
    bool _victory = false;
    player _player;
    bool _game_over = false; // helps stop the game once player gets hit
    int _spawn_timer = 0; // helps deciding when to create a new rock
    bn::vector<rock, 16> _rocks; // this can store up to 16 rocks
    bn::regular_bg_ptr _background;
    bool _lost = false;      // remembers that player got hit
    int _lose_timer = 0;     // short delay before ending round
    static constexpr int _lose_delay = 60; //about 1 second
    int _score = 0; // keeps track of survival score
    
    bn::vector<bn::sprite_ptr, 32> _score_sprites;




};

}

#endif