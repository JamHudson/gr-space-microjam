#include "knc/knc_planet.h"
#include "bn_sprite_items_fire_planet.h"

namespace knc {

/**
 * Constructor — spawns planet at a random x position at the top of the screen
 * 
 * @param random rng from game_data used to pick spawn column
 * @param speed falling speed in pixels per frame
 */

 // 4 frame but start from 0 - looping animation
planet::planet(bn::fixed_point position, bn::fixed speed) :
    _sprite(bn::sprite_items::fire_planet.create_sprite(position)),
    _animation(bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::fire_planet.tiles_item(), 0, 1, 2, 3)),
    _position(position) ,
    _speed(speed)
{
}

/**
 * Called once per frame — moves planet downward
 * animation update here
 */
void planet::update() {
    _position.set_y(_position.y() + _speed);
    _sprite.set_position(_position);
    _animation.update();
}

// returns current position for collision detection with the cat
bn::fixed_point planet::position() const {
    return _position;
}

/**
 * Checks if this planet is colliding with another object
 * 
 * @param other_pos position of the other object
 * @param other_radius collision radius of the other object
 */
bool planet::collides_with(bn::fixed_point other_pos, bn::fixed other_radius) const {
    bn::fixed dx = _position.x() - other_pos.x();
    bn::fixed dy = _position.y() - other_pos.y();
    bn::fixed dist_squared = (dx * dx) + (dy * dy);
    bn::fixed collision_dist = COLLISION_RADIUS + other_radius;
    return dist_squared <= collision_dist * collision_dist;
}

// returns true if planet has fallen past the bottom of the screen
bool planet::off_screen() const {
    bn::fixed offscreen_y = bn::display::height() / 2 +16;
    return _position.y() > offscreen_y;
}

} // namespace knc