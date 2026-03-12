#ifndef MJ_GAME_JINGLE_TYPE_H
#define MJ_GAME_JINGLE_TYPE_H

#include "bn_common.h"

namespace mj
{
    /**
     * @brief Common game jingles.
     */
    enum class game_jingle_type : uint8_t
    {
        METRONOME_12BEAT,
        METRONOME_16BEAT,
        METRONOME_20BEAT,
    };
}

#endif
