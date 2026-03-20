#include "any_game_name.h"
#include "any_platform.h"
#include "bn_sprite_items_astronaut.h"
#include "bn_sprite_items_platform.h"
#include "bn_sprite_items_moon.h"
#include "mj/mj_small_sprite_font.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_items_bg.h"
#include "bn_sound_items.h"

#include "mj/mj_game_list.h"

namespace {
    constexpr bn::string_view code_credits[] = { "Anthony Margullis", "Yousif Sultan" };
    constexpr bn::string_view graphics_credits[] = { "Anthony Margullis", "Yousif Sultan" };
    constexpr bn::string_view sfx_credits[] = {"sodatax"};
    constexpr bn::string_view music_credits[] = {"Anthony Margullis"};
}

MJ_GAME_LIST_ADD(any::any_game_name)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace any {

any_game_name::any_game_name(int completed_games, const mj::game_data& data) :
    mj::game("any"),
    _has_lost(false),
    _completed_games(completed_games)
{

    play_sound(bn::sound_items::any_space_theme, completed_games, data);

    mj::difficulty_level difficulty = recommended_difficulty_level(completed_games, data);

    if (difficulty == mj::difficulty_level::EASY) {
        _platforms[0].set_position(0, 40);
        _platforms[1].set_position(-30, 10);
        _platforms[2].set_position(40, -20); 
        _moon_y = -60;
    }
    else if (difficulty == mj::difficulty_level::NORMAL) {
        _platforms[0].set_position(0, 40);
        _platforms[1].set_position(-50, 5);  
        _platforms[2].set_position(40, -25); 
        _moon_y = -60;
    }
    else { // HARD
        _platforms[0].set_position(0, 40);   
        _platforms[1].set_position(-40, 10);  
        _platforms[2].set_position(59, -30); 
        _moon_y = -65;
    }
    
    _moon_sprite = bn::sprite_items::moon.create_sprite(_moon_x, _moon_y);
    _moon_anim = bn::create_sprite_animate_action_forever(
                *_moon_sprite, 15, bn::sprite_items::moon.tiles_item(), 0, 1, 2, 3);
    
    _player.emplace(0, -20);

    _background = bn::regular_bg_items::bg.create_bg(0, 0);
    
    _background->set_priority(3);

    bn::sprite_text_generator text_generator = data.text_generator;
    text_generator.set_center_alignment();

    bn::string_view diff_text;
    if (difficulty == mj::difficulty_level::EASY) {
        diff_text = "EASY";
    } else if (difficulty == mj::difficulty_level::NORMAL) {
        diff_text = "MEDIUM";
    } else {
        diff_text = "HARD";
    }

    text_generator.generate(0, 55, diff_text, _text_sprites);
}

bn::string<16> any_game_name::title() const {
    return "Grab the Moon";
}

int any_game_name::total_frames() const {
    return 600;
}

mj::game_result any_game_name::play([[maybe_unused]] const mj::game_data& data) {

    int elapsed_frames = total_frames() - data.pending_frames;

    if (elapsed_frames > 0 && elapsed_frames % 445 == 0) {
        play_sound(bn::sound_items::any_space_theme, _completed_games, data);
    }

    if (data.pending_frames < 480 && !_text_sprites.empty()) {
        _text_sprites.clear();
    }

    if(_moon_anim) {
        _moon_anim->update();
    }

    if (_player) {
        _player->update(bn::span<const platform>(_platforms, 3));

        if (_player->dy() == -4.3) {
            play_sound(bn::sound_items::any_spring_jump_sfx, _completed_games, data);
        }

        if (_touched_moon()) { 
            return mj::game_result(true, true); // (finished, victory)
        }

        if (_player->y() > 80) {
            _has_lost = true; 
            return mj::game_result(true,false);
        }

    }

    return mj::game_result(false, false);
}

bool any_game_name::_touched_moon() const {
    if (!_player) {
        return false;
    }

    constexpr int hitbox_size = 12; 

    bn::fixed dx = bn::abs(_player->x() - _moon_x);
    bn::fixed dy = bn::abs(_player->y() - _moon_y);

    return dx < hitbox_size && dy < hitbox_size;
}

bool any_game_name::victory() const {
    if (_has_lost) {
        return false;
    }
    
    return _touched_moon();
}

void any_game_name::fade_in([[maybe_unused]]const mj::game_data& data)
{
}

void any_game_name::fade_out([[maybe_unused]] const mj::game_data& data)
{    
}

}