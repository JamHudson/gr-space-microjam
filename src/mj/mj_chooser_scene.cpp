#include "mj_chooser_scene.h"
#include "mj_scene_type.h"

#include "mj_core.h"
#include "mj_game_list.h"
#include "mj_game.h"

#include <bn_unique_ptr.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_fixed_point.h>
// Tutor debug
#include "bn_sprite_items_mj_small_astro.h"

namespace mj {

chooser_scene::chooser_scene(core& core) :
    _core(core),
    _cursor_idx(_core.sram_data().chosen_game()),
    _cursor(bn::sprite_items::mj_small_astro.create_sprite(12)) {
        bn::backdrop::set_color(bn::color(0, 0, 0));

        auto& text_generator = core.small_text_generator();

        game_data fake_game_data = {
            core.text_generator(),
            core.small_text_generator(),
            core.big_text_generator(),
            core.random(),
            300,
            true // Do not play any music/sounds from the game constructors on the menu screen
        };
        int y = Y_START;
        text_generator.generate({X_START, y}, "All Games", _game_name_sprites);
        y += LINE_HEIGHT;

        bn::unique_ptr<mj::game> game;
        bn::span<game_list::function_type> game_list_entries = game_list::get();

        // If we have an old save file and games have been removed so our saved idx is invalid,
        // default to all games
        if(_cursor_idx >= game_list_entries.size()) {
            _cursor_idx = -1;
        }

        update_cursor_position();

        for(int i = 0; i < game_list_entries.size(); i++) {
            game_list::function_type game_list_entry = game_list_entries[i];
            game.reset(game_list_entry(0, fake_game_data));
            auto title = game->title();
            _game_names.push_back(title);
            text_generator.generate({X_START, y}, title, _game_name_sprites);
            y += LINE_HEIGHT;
        }
        game.reset();
    }

[[nodiscard]] bn::optional<scene_type> chooser_scene::update() {
    bn::optional<scene_type> next_scene = {};

    if(bn::keypad::down_pressed()) {
        _cursor_idx += 1;
        if(_cursor_idx >= _game_names.size()) {
            _cursor_idx = -1;
        }
    }
    if(bn::keypad::up_pressed()) {
        _cursor_idx -= 1;
        if(_cursor_idx < -1) {
            _cursor_idx = _game_names.size() - 1;
        }
    }

    update_cursor_position();

    if(bn::keypad::a_pressed()) {
        auto& sram_data = _core.sram_data();
        sram_data.set_chosen_game(_cursor_idx);
        sram_data.write();
        _core.set_chosen_game(_cursor_idx);
        next_scene.emplace(mj::scene_type::GAME);
    }
    else if(bn::keypad::b_pressed()) {
        next_scene.emplace(mj::scene_type::TITLE);
    }

    return next_scene;
}

void chooser_scene::update_cursor_position() {
    _cursor.set_x(X_START + CURSOR_OFFSET);
    _cursor.set_y(Y_START + ((_cursor_idx + 1) * LINE_HEIGHT));
}


}