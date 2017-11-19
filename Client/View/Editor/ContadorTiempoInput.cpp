#include <iostream>
#include <stdlib.h>
#include "ContadorTiempoInput.h"

ContadorTiempoInput::ContadorTiempoInput(int horda,
                                             SDL_Texture *texture,
                                             Renderer &renderer, Editor &editor)
        : Text(0, 0, HORDA_QUANTITY_HEIGHT, HORDA_QUANTITY_WIDTH, texture,
               renderer), horda(horda), editor(editor) {}

void ContadorTiempoInput::draw(int number, int padding) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    if (hordaNro.quot < padding)
        return;
    div_t enemigoNro = div(hordaNro.rem, HORDA_BUTTONS_PER_ENEMY);
    button.x = enemigoNro.quot * HORDA_ENEMIGO_IMG_SIZE;
    button.y = HORDA_QUANTITY_PADDING +
            (hordaNro.quot - padding) * HORDA_TOTAL_HEIGHT;
    this->text = std::to_string(editor.getTiempoHorda(horda));
    Text::draw(number, 0);
}

bool ContadorTiempoInput::belongsToHorda(int hordaNro) {
    return horda == hordaNro;
}