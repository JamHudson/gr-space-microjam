#include "black_hole.h"
#include "bn_affine_bg_items_background.h"
#include "bn_sprite_items_black_hole.h"
#include "bn_sound_items.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace sno
{

    /**
     * black_hole constructor
     *
     * @param position the location of the black hole
     */
    black_hole::black_hole(bn::fixed_point position)
        : _sprite(bn::sprite_items::black_hole.create_sprite(position)),
          _position(position),
          // this should loop through all 8 frames of the black_hole.bmp
          _sprite_action(bn::create_sprite_animate_action_forever(
              // if you need to change the black hole rotation speed
              // change _sprite, 1, to change the speed of the rotation 1,2,4 or 8
              _sprite, 4,
              bn::sprite_items::black_hole.tiles_item(),
              0, 1, 2)),
          _background(bn::affine_bg_items::background.create_bg(0, 0))
    {
    }

    /**
     * Gets the current position of the black hole.
     *
     * @return the black hole's position as a fixed_point
     */
    bn::fixed_point black_hole::position() const
    {
        return _position;
    }
    // this declares the update method on our black hole
    void black_hole::update()
    {
        _sprite_action.update();
        // background rotation logic
        _rotation -= bn::fixed(2);
        if (_rotation <= -360)
            _rotation += 360;
        _background.set_rotation_angle(-_rotation);
    }
}
