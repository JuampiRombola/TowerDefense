#include <stdlib.h>
#include <iostream>
#include "ContadorEnemigosInput.h"

ContadorEnemigosInput::ContadorEnemigosInput(int horda, std::string enemigo,
                                             SDL_Texture *texture,
                                             Renderer &renderer, Editor &editor)
        : Text(0, 0, HORDA_QUANTITY_HEIGHT, HORDA_QUANTITY_WIDTH, texture,
               renderer), horda(horda), enemigo(std::move(enemigo)),
          editor(editor) {}

void ContadorEnemigosInput::draw(int number) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    div_t enemigoNro = div(hordaNro.rem, HORDA_BUTTONS_PER_ENEMY);
    button.x = enemigoNro.quot * HORDA_ENEMIGO_IMG_SIZE;
    button.y = HORDA_QUANTITY_PADDING +
               hordaNro.quot * HORDA_TOTAL_HEIGHT;
    this->text = std::to_string(
            editor.getCantidadEnemigosEnHorda(enemigo, horda));
    Text::draw(number);
}

