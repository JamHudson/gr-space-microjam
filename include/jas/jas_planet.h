#ifndef JAS_PLANET_H // Include guard must start with the 3-letter id
#define JAS_PLANET_H

#include <bn_regular_bg_ptr.h>
#include <bn_display.h>

// All game functions/classes/variables/constants scoped to the namespace
namespace jas
{

    /**
     * A planet for the ship to land upon -- or crash into.
     */
    class planet
    {
        // (0,0) center, (0,-30) is up, (0, 30) is down
        static constexpr bn::fixed_point PLANET_POSITION = {1, 50};

    public:
        /**
         * planet constructor
         */
        planet();

        void set_visibility(bool setting);

    private:
        // The bg to display the planet
        bn::regular_bg_ptr _bg;
    };
}

#endif