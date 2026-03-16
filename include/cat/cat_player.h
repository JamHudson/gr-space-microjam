#ifndef CAT_PLAYER_H
#define CAT_PLAYER_H

#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_display.h>

namespace cat {

/**
 * A cat astronaut controlled with the d-pad.
 */
class cat_player {
    static constexpr int MAX_X = bn::display::width() / 2;
    static constexpr int MIN_X = -bn::display::width() / 2;
    static constexpr int MAX_Y = bn::display::height() / 2;
    static constexpr int MIN_Y = -bn::display::height() / 2;

public:
    /**
     * @param starting_position where to place the player on screen
     * @param speed pixels per frame in each dimension
     */
    cat_player(bn::fixed_point starting_position, bn::fixed speed);

    /**
     * Reads d-pad input and moves the player for one frame.
     */
    void update();

    /**
     * Returns the current screen position of the player.
     */
    [[nodiscard]] bn::fixed_point position() const;

private:
    bn::sprite_ptr _sprite;
    bn::fixed _speed;
};

}

#endif