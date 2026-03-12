#include "mj/mj_credits_scene.h"

#include "bn_keypad.h"
#include "bn_reciprocal_lut.h"

#include "mj/mj_core.h"
#include "mj/mj_scene_type.h"


namespace mj
{

namespace
{
    constexpr int camera_x = bn::fixed(256 - 12).data();
    constexpr int camera_y = bn::fixed(192).data() >> 4;
    constexpr int camera_cos = 256;
    constexpr int camera_sin = 0;
    constexpr int horizon_y = 80 - 36;
    constexpr int blending_height = 16;
}

credits_scene::credits_scene(core& core) :
    _credits(core)
{
    _update_gfx();
}

bn::optional<scene_type> credits_scene::update()
{
    bn::optional<scene_type> result;

    if(_credits.update())
    {
        _update_gfx();
    }
    else
    {
        result = scene_type::TITLE;
    }

    return result;
}

void credits_scene::_update_gfx()
{
    bn::fixed dir_z = bn::fixed::from_data(8);
    int updates = bn::keypad::a_held() ? credits::speed_up_frames : 1;
    _elapsed_frames += updates;
    _camera_z -= dir_z * camera_cos * updates;
}
}


