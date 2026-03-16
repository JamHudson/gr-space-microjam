#include "knc/knc_enemy.h"
#include "bn_sprite_items_knc_enemy.h"

namespace knc {

enemy::enemy(bn::fixed_point position, bn::fixed speed, int direction) :
    _sprite(bn::sprite_items::knc_enemy.create_sprite(position)),
    _position(position),
    _speed(speed),
    _direction(direction)
{
    //make sure that the enemy sprite appears above the cat
    _sprite.set_z_order(0);
    _sprite.set_horizontal_flip(direction < 0);
    _sprite.set_position(_position);
}

void enemy::update()
{
    _position.set_x(_position.x() + _speed * _direction);
    _sprite.set_position(_position);
}

bn::fixed_point enemy::position() const
{
    return _position;
}

bool enemy::collides_with(bn::fixed_point other_pos, bn::fixed other_radius) const
{
    bn::fixed dx = _position.x() - other_pos.x();
    bn::fixed dy = _position.y() - other_pos.y();
    bn::fixed dist_sq = (dx * dx) + (dy * dy);
    bn::fixed col_dist = COLLISION_RADIUS + other_radius;
    return dist_sq <= col_dist * col_dist;
}

bool enemy::off_screen() const
{
    bn::fixed edge = bn::display::width() / 2 + 20;
    return _position.x() > edge || _position.x() < -edge;
}

} // namespace knc