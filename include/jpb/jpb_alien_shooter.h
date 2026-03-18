#ifndef JPB_ALIEN_SHOOTER_H
#define JPB_ALIEN_SHOOTER_H

#include "mj/mj_game.h"
#include "jpb/jpb_player.h"
#include "jpb/jpb_enemy.h"
#include "jpb/jpb_missile.h"
#include <bn_vector.h>
#include <bn_sprite_text_generator.h>
#include <bn_regular_bg_ptr.h>

namespace jpb {

  static constexpr int MIN_Y = -bn::display::height() / 2;

  class jpb_alien_shooter : public mj::game {
    public: 
      jpb_alien_shooter (int completed_games, const mj::game_data& data);

      bn::string<16> title() const override;

      int total_frames() const override;

      mj::game_result play(const mj::game_data& data) override;

      bool victory() const override;

      void fade_in(const mj::game_data& data) override;

      void fade_out(const mj::game_data& data) override;

      private:
        jpb_player _player;
        jpb_enemy _enemy;
        bn::vector<jpb_missile, 10> _missiles;

        bn::fixed _recommended_player_speed(mj::difficulty_level difficulty);
        bn::fixed _recommended_enemy_speed(mj::difficulty_level difficulty);

        bn::sprite_text_generator _text_generator;
        bn::vector<bn::sprite_ptr, 4> _ammo_sprites;

        bn::regular_bg_ptr _background;
  };
}

#endif