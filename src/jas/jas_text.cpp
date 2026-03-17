#include "jas/jas_text.h"

namespace jas {

  /* Text constructor */
    text::text(const bn::sprite_text_generator& generator) : 
        text_generator(generator) 
    {

    // Generate the sprites and store them in the vector
    text_generator.generate(TEXT_POSITION, instructions, text_sprites);

    // Loop through the generated sprites and set their Z-order
    for(bn::sprite_ptr& text_sprite : text_sprites)
    {
        text_sprite.set_z_order(-10);
    }
  }

}