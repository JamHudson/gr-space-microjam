#ifndef REB_MOON_H
#define REB_MOON_H

#include "bn_sprite_ptr.h"
#include "bn_fixed.h"
#include "bn_optional.h"
#include "bn_sprite_items_reb_moon.h"


namespace reb
{
    class moon
    {
        public:
            /**
             * Constructs the moon, locked to an orbit around the earth
             */
            moon(bn::fixed earth_x, bn::fixed earth_y, bn::fixed orbit_radius, bn::fixed start_angle_degrees, bn::fixed speed_modifier);

            /** Reads keypad and updates position */
            void update();

            /** Current X of the moon. */
            [[nodiscard]] bn::fixed x() const;

            /** Current Y of the moon. */
            [[nodiscard]] bn::fixed y() const;

            /** Current orbital angle in degrees. */
            [[nodiscard]] bn::fixed angle() const;

        private:
            bn::sprite_ptr _moonSprite;
            bn::fixed _earth_x;
            bn::fixed _earth_y;
            bn::fixed _orbit_radius;
            bn::fixed _angle;           // degrees, 0–360
            bn::fixed _angular_speed;   // degrees per frame

            void _update_sprite_position();
    };
}

#endif