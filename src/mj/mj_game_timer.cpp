#include "mj/mj_game_timer.h"

#include "bn_sprite_items_mj_font.h"

#include "bn_sprite_items_mj2_progress_bar.h"

namespace mj
{

namespace
{
    constexpr bn::fixed candle_y = 72;
}

game_timer::game_timer() 
{
}

void game_timer::update(int pending_frames, int total_frames)
{
    BN_ASSERT(pending_frames >= 0, "Invalid pending frames: ", pending_frames);
    BN_ASSERT(total_frames > 0, "Invalid total frames: ", total_frames);

    int width_pixels = (pending_frames * 240) / total_frames;
    BN_ASSERT(width_pixels <= 240, "Invalid width: ", width_pixels);

    int width_sprites = (width_pixels + 16 - 1) / 16;

    if(_sprites.size() > width_sprites)
    {
        _sprites.shrink(width_sprites);
    }

    bn::fixed x = 6 - 120;

    if(int x_desp = width_pixels % 16)
    {
        x -= 16 - x_desp;
    }

    for(int index = 0; index < width_sprites; ++index)
    {
        int tiles_index = 0;

        if(index == width_sprites - 1)
        {
            tiles_index = 1;
        }

        if(_sprites.size() == index)
        {
            bn::sprite_ptr sprite = bn::sprite_items::mj2_progress_bar.create_sprite(x, candle_y, tiles_index);
            sprite.set_z_order(-32767);
            _sprites.push_back(bn::move(sprite));
        }
        else
        {
            bn::sprite_ptr& sprite = _sprites[index];
            sprite.set_x(x);
            sprite.set_tiles(bn::sprite_items::mj2_progress_bar.tiles_item(), tiles_index);
        }

        x += 16;
    }
}

}
