#include <cmath>
#include <iostream>
#include <stdlib.h>
#include "EnemigoImage.h"

EnemigoImage::EnemigoImage(int horda, SDL_Texture *texture, Renderer &renderer)
        : horda(horda),
          Image(0, 0, HORDA_ENEMIGO_IMG_SIZE, HORDA_ENEMIGO_IMG_SIZE, texture,
                renderer) {}

void EnemigoImage::draw(int number) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    div_t enemigoNro = div(hordaNro.rem, HORDA_BUTTONS_PER_ENEMY);
    button.x = enemigoNro.quot * HORDA_ENEMIGO_IMG_SIZE;
    button.y = HORDA_ENEMIGO_PADDING + hordaNro.quot * HORDA_TOTAL_HEIGHT;
    Image::draw(number);
}