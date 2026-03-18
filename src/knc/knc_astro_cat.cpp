#include "knc/knc_astro_cat.h"
#include "mj/mj_game_list.h"

namespace {
    constexpr bn::string_view code_credits[] = { "knc" };
    constexpr bn::string_view graphics_credits[] = { "knc" };
    constexpr bn::string_view sfx_credits[] = { "" };
    constexpr bn::string_view music_credits[] = { "" };
}

namespace knc {

    bn::fixed knc_astro_cat::_recommended_speed(mj::difficulty_level difficulty) {
        if (difficulty == mj::difficulty_level::EASY){
            return 1.5;
        } else if (difficulty == mj::difficulty_level::NORMAL) {
            return 2.5;
        }
        return 3;
    }

    // helper for intial speed
    bn::fixed knc_astro_cat::_initial_speed(int completed_games, const mj::game_data& data) {
        return _recommended_speed(recommended_difficulty_level(completed_games, data));
    }

    knc_astro_cat::knc_astro_cat(int completed_games, const mj::game_data& data)
        : mj::game("knc"),
        _background(),
        _cat(bn::fixed_point(0,40), 2),
        _difficulty(recommended_difficulty_level(completed_games, data)),
      _enemy1(bn::fixed_point(0, -5000), _initial_speed(completed_games, data), 1),
        _enemy1_direction(true),
        _enemy1_delay(180),
        _hit(false)
    {
        bn::fixed speed = _initial_speed(completed_games, data);
        // easy + normal + hard
        _planets.push_back(planet(bn::fixed_point(0, -80), speed));
        _planets.push_back(planet(bn::fixed_point(-50, -120), speed));
        _planets.push_back(planet(bn::fixed_point(50, -247), speed));

        // normal + hard ( planet 4, star 1, star 2)
        if(_difficulty == mj::difficulty_level::NORMAL || _difficulty == mj::difficulty_level::HARD) {
            _planets.push_back(planet(bn::fixed_point(30, -440), speed));
            _stars.push_back(shooting_star(bn::fixed_point(-120, -30), speed));
            _stars.push_back(shooting_star(bn::fixed_point(-340, 0), speed));
        }
    }

    bn::string<16> knc_astro_cat::title() const { return "Dodge Them Fire!"; }
    int knc_astro_cat::total_frames() const { return 60 * 5; }

    void knc_astro_cat::_spawn_enemy(const mj::game_data& data, bn::fixed speed) {
        bn::fixed y = bn::fixed(data.random.get_int(100)) - 50; // random y position for enemy
        _enemy1 = enemy(bn::fixed_point(-120, y), speed, 1);    // spawn from left moving right
    }

    void knc_astro_cat::_respawn_enemy(const mj::game_data& data, bn::fixed speed) {
        _enemy1_direction = !_enemy1_direction; // alternate spawn direction
        int dir = _enemy1_direction ? 1 : -1; // direction multiplier for speed
        bn::fixed spawn_x = _enemy1_direction ? bn::fixed(-120) : bn::fixed(120); // spawn from left or right based on direction
        bn::fixed y = bn::fixed(data.random.get_int(100)) - 50;   // random y position
        _enemy1 = enemy(bn::fixed_point(spawn_x, y), speed, dir); // spawn enemy with new position and direction
    }

    void knc_astro_cat::_update_enemy(const mj::game_data& data, bn::fixed speed) {
        if (_enemy1_delay > 0) {
            _enemy1_delay--; // decrease delay
            // spawn enemy when delay expires
            if (_enemy1_delay == 0) {
                _spawn_enemy(data, speed);
            }
        } else {
            // update enemy if active
            _enemy1.update();

            // IF the enemy goes off screen
            if (_enemy1.off_screen()) {
                _respawn_enemy(data, speed); // respawn enemy from alternate side
            }
        }
    }

    mj::game_result knc_astro_cat::play(const mj::game_data& data)
    {
        bn::fixed speed = _recommended_speed(_difficulty);
        _background.update();
        _cat.update();

        for (planet& p : _planets) {
            p.update();
            if(p.off_screen()){
                p = planet(bn::fixed_point(bn::fixed(data.random.get_int(200)) - 100, -80), speed);
            }
        }

        // update all shooting stars
        for(shooting_star& s : _stars) {
            s.update();
            if(s.off_screen()) {
                s = shooting_star(bn::fixed_point(-120, bn::fixed(data.random.get_int(140)) - 70), speed);
            }
        }

        // hard mode — update enemy (delay, spawn, move, respawn)
        if(_difficulty == mj::difficulty_level::HARD)
        {
            _update_enemy(data, speed);
        }

        // collision: planets
        for(planet& p : _planets) {
            if(p.collides_with(_cat.position(), cat::COLLISION_RADIUS)) {
                _hit = true;
            }
        }

        // collision: shooting stars
        for(shooting_star& s : _stars) {
            if(s.collides_with(_cat.position(), cat::COLLISION_RADIUS)) {
                _hit = true;
            }
        }

        // collision: enemy (hard only, after delay expires)
        if(_difficulty == mj::difficulty_level::HARD && _enemy1_delay == 0) {
            if(_enemy1.collides_with(_cat.position(), cat::COLLISION_RADIUS)) {
                _hit = true;
            }
        }

        // end game if cat got hit
        return mj::game_result(_hit, false);
    }

    // if cat never got hit - Win
    bool knc_astro_cat::victory() const { return !_hit; }
    void knc_astro_cat::fade_in(const mj::game_data&) {}
    void knc_astro_cat::fade_out(const mj::game_data&) {}

} // namespace knc

MJ_GAME_LIST_ADD(knc::knc_astro_cat)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)