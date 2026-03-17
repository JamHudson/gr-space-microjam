#include <bn_keypad.h>
#include <bn_sprite_item.h>

#include "aaa_planetoid.h"
#include "mj/mj_game_list.h"
#include "mj/mj_game_data.h"
#include "bn_display.h"
#include "bn_sprite_items_aaa_heart.h"
#include "bn_regular_bg_items_aaa_bg.h"
#include <bn_core.h>
#include <bn_log.h>
#include "bn_sound_items.h"

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
                                                                                                                       _player(bn::fixed_point(0, 0)),
                                                                                                                       _background(bn::regular_bg_items::aaa_bg.create_bg())
    {
        _asteroids = _recommended_enemy_kill(recommended_difficulty_level(completed_games, data));
        _hp = 3;

        for (int i = 0; i < _enemies.max_size(); i++)
        {
            bn::fixed x = data.random.get_int(-200, 200);
            bn::fixed y = data.random.get_int(-100, 100);

            // these if statements add the desired buffer to the value after its generated to garunteed that no
            // asteroids spawn within that range
            if (x < 0)
                x -= 40;
            else
                x += 40;

            if (y < 0)
                y -= 40;
            else
                y += 40;

            bn::fixed_point pos(x, y);

            _enemies.push_back(aaa_enemy({pos}, .6));
        }
        play_sound(bn::sound_items::aaa_music, completed_games, data);
    }

    bn::string<16> aaa_planetoids::title() const
    {
        bn::string<16> title = "Destroy ";
        title.append(bn::to_string<2>(_asteroids));
        title.append(" rocks");
        return title;
    }

    int aaa_planetoids::total_frames() const
    {
        return 480;
    }

    mj::game_result aaa_planetoids::play([[maybe_unused]] const mj::game_data &data)
    {
        _player.update();
        _updateHP(_hp);

        if (bn::keypad::a_pressed())
        {
            if (_bullets.size() != _bullets.max_size())
            {
                _bullets.push_back(aaa_Bullet(bn::fixed_point(0, 0), 5, _player.getAngle()));
            }
        }

        for (int i = _enemies.size() - 1; i >= 0; i--)
        {
            _enemies[i].update();
            if (_enemies[i].getRect().intersects(_player.getRect()))
            {
                _hp--;
                _asteroids = _asteroids - 1; // Even if the asteroid hits the player, it still counts as towards the win conditon
                _enemies.erase(_enemies.begin() + i);
                return mj::game_result(_hp == 0, false); // the game will end if the player is hit 3 times.
            }
        }

        _checkHit(_enemies, _bullets, _asteroids);
        BN_LOG(_asteroids);

        return mj::game_result(victory(), false);
    }

    bool aaa_planetoids::victory() const
    {
        return _asteroids <= 0;
    }

    void aaa_planetoids::fade_in([[maybe_unused]] const mj::game_data &data)
    {
    }

    void aaa_planetoids::fade_out([[maybe_unused]] const mj::game_data &data)
    {
    }

    bn::fixed aaa_planetoids::_recommended_enemy_kill(mj::difficulty_level difficulty)
    {
        if (difficulty == mj::difficulty_level::EASY)
        {
            return 3;
        }
        else if (difficulty == mj::difficulty_level::NORMAL)
        {
            return 5;
        }
        return 10;
    }

    void aaa_planetoids::_checkHit(bn::vector<aaa_enemy, 12> &enemies, bn::vector<aaa_Bullet, 25> &bullets, bn::fixed &asteroids)
    {
        // I am aware that this is a nested for loop, but trying to make this operate inside the classes would have required passing in the information for the enemy vector
        // I am not at this time able to dedicate that much mental power to solve this, so i instead have a nested loop to check each bullet to each enemy
        for (int i = bullets.size() - 1; i >= 0; i--)
        {
            bullets[i].update();

            for (int j = 0; j < enemies.size(); j++)
            {
                if (bullets[i].getRect().intersects(enemies[j].getRect()))
                {

                    if (!_enemies[j].is_destroyed()) // this makes sure that the enemies destroyed boolean isnt already toggle to prevent duplicate calls
                    {
                        _enemies[j].destroyedAnimation(); // toggles boolean to create/start animation
                        asteroids = asteroids - 1;        // placing this asteroid decrementer here worked best for triggering correct win condition
                    }
                    if (_enemies[j].animation_done()) // only deletes if animation is finished
                    {
                        _enemies.erase(_enemies.begin() + j);
                    }
                }
            }
            if (_outOfBounds(bullets[i]))
            {
                bullets.erase(bullets.begin() + i);
            }
        }
    }

    bool aaa_planetoids::_outOfBounds(aaa_Bullet bullet)
    {
        bn::fixed bX = bullet.BulletPos().x();
        bn::fixed bY = bullet.BulletPos().y();
        return bX > bn::display::width() / 2 || bY > bn::display::height() / 2 || bX < -bn::display::width() / 2 || bY < -bn::display::height() / 2;
    }

    void aaa_planetoids::_updateHP(int &hp)
    {
        int x = -100;
        _hpSprites.clear();
        for (int i = 0; i < hp; i++)
        {
            _hpSprites.push_back(bn::sprite_items::aaa_heart.create_sprite(x, -70));
            x += 20;
        }
    }
}