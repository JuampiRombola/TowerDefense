#include "EnemigoImage.h"

EnemigoImage::EnemigoImage(int horda, SDL_Texture *texture, Renderer &renderer)
        : horda(horda),
          Image(0, 0, HORDA_ENEMIGO_IMG_SIZE, HORDA_ENEMIGO_IMG_SIZE, texture,
                renderer) {}

void EnemigoImage::draw(int number) {
    button.x = ((number - TOTAL_MAIN_BUTTONS) % HORDA_TOTAL_ENEMIES) *
               HORDA_ENEMIGO_IMG_SIZE;
    button.y = HORDA_ENEMIGO_PADDING +
               (number - TOTAL_MAIN_BUTTONS) * HORDA_TOTAL_HEIGHT /
               (HORDA_TOTAL_BUTTONS);
    Image::draw(number);
}