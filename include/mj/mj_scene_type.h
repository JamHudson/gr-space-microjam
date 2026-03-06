#ifndef MJ_SCENE_TYPE_H
#define MJ_SCENE_TYPE_H

#include "bn_common.h"

namespace mj
{
    enum class scene_type : uint8_t
    {
        INTRO,
        TITLE,
        OPENING_A,
        OPENING_B,
        OPENING_C,
        OPENING_D,
        OPENING_E,
        OPENING_F,
        OPENING_G,
        GAME,
        GAME_ZOOM_OUT,
        CREDITS,
        CHOOSER
    };
}

#endif
