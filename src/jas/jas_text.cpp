#include "jas/jas_text.h"

namespace jas {

  /* Text constructor */
    text::text(const bn::sprite_text_generator& generator) : 
        _text_generator(generator) 
    {

    // Generate the sprites and store them in the vector
    _text_generator.generate(_TEXT_POSITION, _instructions, _text_sprites);

    // Loop through the generated sprites and set their Z-order
    for(bn::sprite_ptr& text_sprite : _text_sprites)
    {
        text_sprite.set_z_order(-10);
    }
  }

}