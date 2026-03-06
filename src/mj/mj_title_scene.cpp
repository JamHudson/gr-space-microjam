#include "mj/mj_title_scene.h"

#include "bn_blending.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_sprite_double_size_mode.h"
#include "bn_string.h"

#include "mj/mj_build_config.h"
#include "mj/mj_core.h"
#include "mj/mj_scene_type.h"
#include "mj/mj_title_backdrop_1.h"

#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_sprite_items_mj_small_pumpkin.h"

namespace mj
{

namespace
{
    constexpr int fade_frames = title_backdrop::fade_frames;
    constexpr int title_frames = 128;
}

title_scene::title_scene(core& core) :
    _cursor_sprite(bn::sprite_items::mj_small_pumpkin.create_sprite(0, 0, 12)),
    _affine_mat(bn::sprite_affine_mat_ptr::create()),
    _affine_mat_hbe(bn::sprite_affine_mat_attributes_hbe_ptr::create(_affine_mat, _affine_mat_attributes))
{

    _backdrop.reset(new title_backdrop_1());

    bn::bg_palettes::set_fade(bn::color(), 1);
    _bgs_fade_action.emplace(fade_frames, 0);

    bn::blending::set_transparency_alpha(0);
    bn::sprite_palettes::set_fade(bn::color(), 1);
    _sprites_fade_action.emplace(fade_frames, 0);

    bn::string<20> high_score_text("HIGH SCORE: ");
    high_score_text.append(bn::to_string<8>(core.sram_data().high_scores()[0]));

    bn::sprite_text_generator& text_generator = core.small_text_generator();
    text_generator.set_center_alignment();
    text_generator.generate(-22, 12 - (160 / 2), high_score_text, _high_score_sprites);
    text_generator.set_left_alignment();
    text_generator.generate(-14, 32, "PLAY", _play_sprites);
    text_generator.generate(-14, 32 + 12, "CREDITS", _credits_sprites);
    text_generator.generate(-14, 32 + 24, "DEBUG", _debug_sprites);
    text_generator.set_right_alignment();
    text_generator.generate(120 - 12, 80 - 12, MJ_VERSION, _version_sprites);
    text_generator.set_left_alignment();
    _cursor_sprite.set_position(_play_sprites[0].position() - bn::fixed_point(28, 0));

    _set_menu_visible(true);

    // TODO: Replace with your music
    //bn::music_items::YOUR_MUSIC.play(0.55);
}

title_scene::~title_scene()
{
    bn::bg_palettes::set_fade_intensity(0);
    bn::sprite_palettes::set_fade_intensity(0);
}

bn::optional<scene_type> title_scene::update()
{
    bn::optional<scene_type> result;
    _update_bgs();

    if(_sprites_fade_action)
    {
        _sprites_fade_action->update();

        if(_music_volume_action)
        {
            _music_volume_action->update();
        }

        if(_sprites_fade_action->done())
        {
            _sprites_fade_action.reset();
            _music_volume_action.reset();
            result = _next_scene;
        }
    }
    else
    {
        _update_menu();
    }

    return result;
}

void title_scene::_update_bgs()
{
    if(_bgs_fade_action)
    {
        _bgs_fade_action->update();

        if(_bgs_fade_action->done())
        {
            _bgs_fade_action.reset();
        }
    }

    if(bn::optional<bn::fixed> fade_intensity = _backdrop->update())
    {
        if(! _bgs_fade_action && ! _next_scene)
        {
            _bgs_fade_action.emplace(fade_frames, *fade_intensity);
        }
    }
}



void title_scene::_set_menu_visible(bool visible)
{
    _cursor_sprite.set_visible(visible);

    for(bn::sprite_ptr& sprite : _high_score_sprites)
    {
        sprite.set_visible(visible);
    }

    for(bn::sprite_ptr& sprite : _play_sprites)
    {
        sprite.set_visible(visible);
    }

    for(bn::sprite_ptr& sprite : _credits_sprites)
    {
        sprite.set_visible(visible);
    }

    for(bn::sprite_ptr& sprite : _version_sprites)
    {
        sprite.set_visible(visible);
    }
}

void title_scene::_update_menu()
{
    bn::fixed play_y = _play_sprites[0].y();
    bn::fixed credits_y = _credits_sprites[0].y();
    bn::fixed debug_y = _debug_sprites[0].y();
    bn::fixed cursor_y = _cursor_sprite.y();

    if(bn::keypad::up_pressed())
    {
        if(cursor_y == play_y)
        {
            _cursor_sprite.set_y(debug_y);
        }
        else if(cursor_y == credits_y)
        {
            _cursor_sprite.set_y(play_y);
        } else 
        {
            _cursor_sprite.set_y(credits_y);
        }

        // TODO: Your cursor sound
        //bn::sound_items::mj_pause_cursor.play();
    }
    else if(bn::keypad::down_pressed())
    {
        if(cursor_y == play_y)
        {
            _cursor_sprite.set_y(credits_y);
        }
        else if(cursor_y == credits_y)
        {
            _cursor_sprite.set_y(debug_y);
        } else 
        {
            _cursor_sprite.set_y(play_y);
        }

        // TODO: Your cursor sound
        //bn::sound_items::mj_pause_cursor.play();
    }
    else if(bn::keypad::a_pressed())
    {
        if(cursor_y == play_y)
        {
            _next_scene = scene_type::GAME;
        }
        else if(cursor_y == credits_y)
        {
            _next_scene = scene_type::CREDITS;
        }
        else if(cursor_y == debug_y) 
        {
            _next_scene = scene_type::CHOOSER;
        }

        if(! _bgs_fade_action)
        {
            _bgs_fade_action.emplace(fade_frames, 1);
        }

        if(bn::music::playing())
        {
            _music_volume_action.emplace(fade_frames, 0);
        }

        _sprites_fade_action.emplace(fade_frames, 1);
        _cursor_sprite.set_tiles(bn::sprite_items::mj_small_pumpkin.tiles_item(), 13);
        // TODO: YOUR STARTING GAME SOUND
        //bn::sound_items::mj_pause_begin.play();
    }
}

}
