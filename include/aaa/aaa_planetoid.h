
#ifndef AAA_PLANETOID_H
#define AAA_PLANETOID_H

#include <bn_regular_bg_ptr.h>
#include "mj/mj_game.h"
#include "aaa/aaa_enemy.h"
#include "aaa/aaa_player.h"
#include "aaa/aaa_bullet.h"

namespace aaa
{
    class aaa_planetoids : public mj::game
    {
    public:
        aaa_planetoids(int completed_games, const mj::game_data &data);
        /**
         * The instructions given to the player at the beginning of the microgame.
         *
         * Must be <= 16 characters long
         */
        bn::string<16> title() const override;

        /**
         * How long the timer for the game should be set to in frames.
         *
         * GBA runs at approx 60 frames per second.
         */
        int total_frames() const override;

        /**
         * play is repeatedly called while the microgame is playing.
         *
         * You can think of it as what previously was in the while event loop.
         * You do NOT need to write your own while event loop
         * You do NOT need to call bn::core::update()
         *
         * @param data shared information, such as a rng and number of frames left in the microgame
         * @return the mj::game result indicating whether the game has finished and whether the title should be hidden
         */
        mj::game_result play(const mj::game_data &data) override;

        /**
         * Returns whether the player has won the microgame.
         *
         * In this particular microgame the player wins if they make the ball leave the screen.
         */
        bool victory() const override;

        /**
         * Called repeatedly as the game fades into view. Unused for this particular microgame.
         *
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        void fade_in(const mj::game_data &data) override;

        /**
         * Called repeatedly as the game fades into view. Unused for this particular microgame.
         *
         * @param data shared information, such as a rng and number of frames left in the microgame
         */
        void fade_out(const mj::game_data &data) override;


    private:
        aaa_Player _player;
        bn::vector<aaa_enemy, 12> _enemies;
        bn::vector<aaa_Bullet, 25> _bullets;
        bn::fixed _recommended_enemy_kill(mj::difficulty_level difficulty);
        bn::fixed _recommended_enemy_speed(mj::difficulty_level difficulty);
        bn::fixed _asteroids;
        bn::vector<bn::sprite_ptr, 3> _hpSprites;
        bn::vector<bn::sprite_ptr, 2> _text_sprites;
        bn::regular_bg_ptr _background;
        int _hp;
        void _checkHit(bn::vector<aaa_enemy, 12> &enemies, bn::vector<aaa_Bullet, 25> &bullets, bn::fixed &asteroids);
        bool _outOfBounds(aaa_Bullet bullet);
        void _updateHP(int &hp);
    };
}

#endif