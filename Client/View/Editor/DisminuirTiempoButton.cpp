#include <stdlib.h>
#include "DisminuirTiempoButton.h"

DisminuirTiempoButton::DisminuirTiempoButton(int horda, SDL_Texture *texture,
                                             MousePosition &mousePosition,
                                             Renderer &renderer, Editor &editor)
        : Button(0, 0, HORDA_MODIFY_QUANTITY_SIZE, HORDA_MODIFY_QUANTITY_SIZE,
                 texture, mousePosition, renderer), horda(horda),
          editor(editor) {}

void DisminuirTiempoButton::click() {
    editor.disminuirTiempoHorda(horda);
}

void DisminuirTiempoButton::draw(int number, int padding) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    if (hordaNro.quot < padding)
        return;
    div_t enemigoNro = div(hordaNro.rem, HORDA_BUTTONS_PER_ENEMY);
    button.x = enemigoNro.quot * HORDA_ENEMIGO_IMG_SIZE;
    button.y = HORDA_MODIFY_QUANTITY_PADDING +
               (hordaNro.quot - padding) * HORDA_TOTAL_HEIGHT;
    Button::draw(number, 0);

}

bool DisminuirTiempoButton::belongsToHorda(int hordaId) {
    return horda == hordaId;
}
