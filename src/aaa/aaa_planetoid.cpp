#include <bn_keypad.h>

#include "aaa_planetoid.h"
#include "mj/mj_game_list.h"
#include "bn_display.h"
#include <bn_core.h>
namespace
{
    constexpr bn::string_view code_credits[] = {"KJ, Adam Kurfurst"};
    constexpr bn::string_view graphics_credits[] = {"KJ, Adam Kurfurst"};
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(aaa::aaa_planetoids) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace aaa
{

    aaa_planetoids::aaa_planetoids([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("aaa"),
                                                                                                                       _player(bn::fixed_point(0, 0))
    {
        _asteroids = _recommended_enemy_kill(recommended_difficulty_level(completed_games, data));

            for (int i = 0; i < _enemies.max_size(); i++)
        {
            bn::fixed_point pos(data.random.get_int(-250, 250), data.random.get_int(-100, 100)); // added extra so some _enemies spawn off-screen
            //bn::fixed speed = data.random.get_fixed(.2, .4);                                     // nice slow moving _enemies

            _enemies.push_back(aaa_enemy({pos}, .6));
        }
    }

    bn::string<16> aaa_planetoids::title() const
    {
        return "Shoot Asteroids!";
    }

    int aaa_planetoids::total_frames() const
    {
        return 480;
    }

    mj::game_result aaa_planetoids::play([[maybe_unused]] const mj::game_data &data)
    {
        _player.update();

        if (bn::keypad::a_pressed())
        {
            if (_bullets.size() != _bullets.max_size()) // this makes it so that only the max amount of _bullets can be on screen at a time, i tried to resize rthe _bullets vector but could not so i did this bandaid fix
            {
                _bullets.push_back(aaa_Bullet(bn::fixed_point(0, 0), 5, _player.getAngle()));
            }
        }

        for (int i = 0; i < _enemies.size(); i++)
        {
            _enemies[i].update();
        }

        // I am aware that this is a nested for loop, but trying to make this operate inside the classes would have required passing in the information for the enemy vector
        // I am not at this time able to dedicate that much mental power to solve this, so i instead have a nested loop to check each bullet to each enemy
        for (int i = _bullets.size() - 1; i >= 0; i--)
        {
            _bullets[i].update();

            bn::fixed bX = _bullets[i].BulletPos().x();
            bn::fixed bY = _bullets[i].BulletPos().y();

            for (int j = 0; j < _enemies.size(); j++)
            {
                if (_bullets[i].getRect().intersects(_enemies[j].getRect()))
                {
                    _enemies.erase(_enemies.begin() + j);
                    _asteroids = _asteroids - 1;
                }
            }
            if (bX > bn::display::width() / 2 || bY > bn::display::height() / 2 || bX < -bn::display::width() / 2 || bY < -bn::display::height() / 2)
            {
                _bullets.erase(_bullets.begin() + i);
            }
        }

        return mj::game_result(_asteroids == 0, false);
    }

    bool aaa_planetoids::victory() const
    {
        // kind of jank but it works if we are hardcoding the inital amount of _enemies
        // if (_enemies.max_size() - _enemies.size() > 1)
        // {
        //     return true;
        // }
        // return false;
        return _asteroids == 0;
    }

    void aaa_planetoids::fade_in([[maybe_unused]] const mj::game_data &data)
    {
    }

    void aaa_planetoids::fade_out([[maybe_unused]] const mj::game_data &data)
    {
    }

    bn::fixed aaa_planetoids::_recommended_enemy_kill(mj::difficulty_level difficulty) {
        if(difficulty == mj::difficulty_level::EASY) {
            return 3;
        } else if (difficulty == mj::difficulty_level::NORMAL) {
            return 5;
        } 
        return 10;
}
}