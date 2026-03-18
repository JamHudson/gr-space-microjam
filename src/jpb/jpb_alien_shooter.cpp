#include "jpb/jpb_alien_shooter.h"
#include "mj/mj_game_list.h"
#include "bn_regular_bg_items_backdrop.h"
#include "bn_sprite_animate_actions.h"


namespace
{
    constexpr bn::string_view code_credits[] = { "Johncarlo", "John Baltazar" };
    constexpr bn::string_view graphics_credits[] = { "Johncarlo", "John Baltazar" };
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

MJ_GAME_LIST_ADD(jpb::jpb_alien_shooter) 
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)


namespace jpb {
    static constexpr bn::size PLAYER_SIZE = {16, 8};
    static constexpr bn::size ENEMY_SIZE = {8, 8};

    jpb_alien_shooter::jpb_alien_shooter([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) :
        mj::game("jpb"),
        _player(jpb_player({0, 30}, _recommended_player_speed(recommended_difficulty_level(completed_games, data)), 
                        PLAYER_SIZE)),
        _enemy(jpb_enemy({0, -30}, _recommended_enemy_speed(recommended_difficulty_level(completed_games, data)),
                        ENEMY_SIZE)),
        _text_generator(data.text_generator),
        _background(bn::regular_bg_items::backdrop.create_bg(0, 0))
    {}

    bn::string<16> jpb_alien_shooter::title() const {
        return "Shoot the alien";
    }

    bn::fixed jpb_alien_shooter::_recommended_player_speed(mj::difficulty_level difficulty) {
        if (difficulty == mj::difficulty_level::EASY) {
            return 3;
        } else if (difficulty == mj::difficulty_level::NORMAL) {
            return 2;
        } 
        return 1.5;
    }

    bn::fixed jpb_alien_shooter::_recommended_enemy_speed(mj::difficulty_level difficulty) {
        if (difficulty == mj::difficulty_level::EASY) {
            return 1;
        } else if (difficulty == mj::difficulty_level::NORMAL) {
            return 2;
        } 
        return 3;
    }

    int jpb_alien_shooter::total_frames() const {
        return 300;
    }

    mj::game_result jpb_alien_shooter::play([[maybe_unused]] const mj::game_data& data) {
        _player.update();
        _enemy.update();
        _ammo_sprites.clear();
        _text_generator.generate(80, -70, bn::to_string<4> (_player.get_missile_count()), _ammo_sprites);

        _player.shoot(_missiles);
        
        for (auto it = _missiles.begin(); it < _missiles.end();) {
            it->update();
            if (it->_sprite.y() <= MIN_Y) {
                it = _missiles.erase(it);
            } else {
                it++;
            }
        }

        mj::game_result result(victory(), false);
        return result;
    }

    bool jpb_alien_shooter::victory() const {
        return _enemy.enemy_shot(_missiles);
    }

    void jpb_alien_shooter::fade_in([[maybe_unused]] const mj::game_data& data) {

    }

    void jpb_alien_shooter::fade_out([[maybe_unused]] const mj::game_data& data) {

    }
    
}