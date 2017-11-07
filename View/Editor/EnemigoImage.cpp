#include <cmath>
#include <iostream>
#include <stdlib.h>
#include "EnemigoImage.h"

EnemigoImage::EnemigoImage(int horda, SDL_Texture *texture, Renderer &renderer)
        : horda(horda),
          Image(0, 0, HORDA_ENEMIGO_IMG_SIZE, HORDA_ENEMIGO_IMG_SIZE, texture,
                renderer) {}

void EnemigoImage::draw(int number) {
    div_t division = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    button.x = ((number - TOTAL_MAIN_BUTTONS) % HORDA_TOTAL_ENEMIES) *
               HORDA_ENEMIGO_IMG_SIZE;
    button.y = HORDA_ENEMIGO_PADDING + division.quot * HORDA_TOTAL_HEIGHT;
    Image::draw(number);
}