#include "jas/jas_planet.h"

#include <bn_keypad.h>
#include <bn_regular_bg_ptr.h>

#include "bn_regular_bg_items_jas_planet_bg.h"
#include "bn_regular_bg_items_temp_planet_choc_milk.h"

// All game functions/classes/variables/constants scoped to the namespace
namespace jas {

  /**
   * planet constructor
   * 
   * @param position the location to put the planet
   */
  planet::planet() :
      // Use regular_bg_items and create_bg
      _bg(bn::regular_bg_items::temp_planet_choc_milk.create_bg(PLANET_POSITION))
  {
      // Backgrounds use set_priority instead of set_z_order
      _bg.set_priority(1); 
      _bg.set_visible(true);
  }

  void planet::set_visibility(bool setting) {
    _bg.set_visible(setting);

  }
}