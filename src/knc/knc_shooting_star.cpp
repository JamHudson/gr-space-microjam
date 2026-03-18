#include "knc/knc_shooting_star.h"
#include "bn_sprite_items_shootingstar.h"

namespace knc {

// spawn shooting star
shooting_star::shooting_star(bn::fixed_point position, bn::fixed speed) :
    _sprite(bn::sprite_items::shootingstar.create_sprite(position)),
    _animation(bn::create_sprite_animate_action_forever(_sprite, 8, bn::sprite_items::shootingstar.tiles_item(), 0,1,2,3)),
    _position(position),
    _speed(speed)
{}

// move shooting star horizontally once per frame is using x
void shooting_star::update() {
    _position.set_x(_position.x() + _speed);
    _sprite.set_position(_position);
    _animation.update();
}

// return current position for collision detection
bn::fixed_point shooting_star::position() const {
    return _position;
}

// check if this shooting star overlaps with another object
// same thing we use for planet, the only different is one horizontal and one vertical
bool shooting_star::collides_with(bn::fixed_point other_pos, bn::fixed other_radius) const {
    bn::fixed dx = _position.x() - other_pos.x();
    bn::fixed dy = _position.y() - other_pos.y();
    bn::fixed dist_squared = (dx * dx) + (dy * dy);
    bn::fixed collision_dist = COLLISION_RADIUS + other_radius;
    return dist_squared <= collision_dist * collision_dist;
}

// returns true if shooting star has gone past the right side of the screen
bool shooting_star::off_screen() const {
    return _position.x() > OFFSCREEN_X;
}

} // namespace knc