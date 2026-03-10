#include "mj/mj_game.h"

#include "bn_core.h"
#include "bn_music.h"

#include "mj/mj_build_config.h"

#include "bn_music_items.h"

namespace mj
{

int game::recommended_total_frames(int base_total_frames, int completed_games, const game_data& data)
{
    bn::fixed tempo = recommended_music_tempo(completed_games, data);
    int total_frames = (base_total_frames / tempo).right_shift_integer();
    BN_ASSERT(total_frames >= minimum_frames && total_frames <= maximum_frames,
              "Invalid base total frames: ", base_total_frames, " - ", tempo, " - ", total_frames);

    return total_frames;
}

difficulty_level game::recommended_difficulty_level(int completed_games, [[maybe_unused]] const game_data& data)
{
    return difficulty_level(bn::clamp(completed_games, 0, 2));
}

bn::fixed game::recommended_music_tempo(int completed_games, [[maybe_unused]] const game_data& data)
{
    constexpr bn::fixed minimum_tempo = 1.15;
    constexpr bn::fixed maximum_tempo = 1.85;
    constexpr bn::fixed tempo_diff = maximum_tempo - minimum_tempo;
    constexpr int minimum_waves = 0;
    constexpr int maximum_waves = 45 / games_per_speed_inc;

    int completed_waves = bn::clamp(completed_games / games_per_speed_inc, minimum_waves, maximum_waves);
    return minimum_tempo + ((completed_waves * tempo_diff) / maximum_waves);
}

void game::play_music(bn::music_item music_item, int completed_games, const game_data& data)
{
    bn::music::play(music_item, 0.5, false);
    bn::music::set_tempo(recommended_music_tempo(completed_games, data));
}

void game::play_sound(bn::sound_item sound_item, int completed_games, const game_data& data)
{
    sound_item.play(1, recommended_music_tempo(completed_games, data), 0);
}

int game::play_jingle(game_jingle_type jingle, int completed_games, const game_data& data)
{
    bn::fixed base_seconds = 8;

    switch(jingle)
    {

    case game_jingle_type::METRONOME_12BEAT:
        play_music(bn::music_items::mj_metronome_12beat, completed_games, data);
        base_seconds = 6;
        break;

    default:
        BN_ERROR("Unknown jingle: ", int(jingle));
        break;
    }

    int base_total_frames = (base_seconds * 60).right_shift_integer() - 24 - 24;
    return recommended_total_frames(base_total_frames, completed_games, data);
}

game::~game()
{
    bn::core::set_assert_tag(MJ_VERSION);
}

void game::on_pause_start(const game_data&)
{
}

void game::on_pause_end(const game_data&)
{
}

game::game(const bn::string_view& id) :
    _assert_tag(id)
{
    _assert_tag += ' ';
    _assert_tag += MJ_VERSION;
    bn::core::set_assert_tag(_assert_tag);
}

}
