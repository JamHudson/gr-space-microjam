#ifndef JPB_ALIEN_SHOOTER_H
#define JPB_ALIEN_SHOOTER_H

#include "mj/mj_game.h"
#include "jpb/jpb_player.h"

namespace jpb {
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
      
  };
}

#endif