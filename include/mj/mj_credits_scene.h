#ifndef MJ_CREDITS_SCENE_H
#define MJ_CREDITS_SCENE_H

#include "bn_affine_bg_attributes.h"
#include "bn_affine_bg_attributes_hbe_ptr.h"
#include "bn_affine_bg_dx_register_hbe_ptr.h"
#include "bn_affine_bg_dy_register_hbe_ptr.h"
#include "bn_affine_bg_pa_register_hbe_ptr.h"
#include "bn_affine_bg_ptr.h"
#include "bn_blending_transparency_attributes.h"
#include "bn_blending_transparency_attributes_hbe_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "mj_credits.h"
#include "mj_scene.h"

namespace mj
{

class core;

class credits_scene final : public scene
{

public:
    explicit credits_scene(core& core);

    [[nodiscard]] bn::optional<scene_type> update() final;

private:
    alignas(int) int16_t _pa_values[160];
    alignas(int) int _dx_values[160];
    alignas(int) int _dy_values[160];
    mj::credits _credits;
    bn::fixed _camera_z;
    int _elapsed_frames = 0;

    void _update_gfx();
};

}

#endif
