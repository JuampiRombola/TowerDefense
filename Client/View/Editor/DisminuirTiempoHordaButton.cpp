#include <stdlib.h>
#include "DisminuirTiempoHordaButton.h"

DisminuirTiempoHordaButton::DisminuirTiempoHordaButton(int horda, SDL_Texture *texture,
                                             MousePosition &mousePosition,
                                             Renderer &renderer, Editor &editor)
        : Button(0, 0, HORDA_MODIFY_QUANTITY_SIZE, HORDA_MODIFY_QUANTITY_SIZE,
                 texture, mousePosition, renderer), horda(horda),
          editor(editor) {}

void DisminuirTiempoHordaButton::click() {
    editor.disminuirTiempoHorda(horda);
}

void DisminuirTiempoHordaButton::draw(int number, int padding) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    if (hordaNro.quot < padding)
        return;
    div_t enemigoNro = div(hordaNro.rem, HORDA_BUTTONS_PER_ENEMY);
    button.x = enemigoNro.quot * HORDA_ENEMIGO_IMG_SIZE + HORDA_QUANTITY_WIDTH + SCROLL_BUTTON_SIZE;
    button.y = renderer.getWindowHeight() -
               HORDA_MODIFY_QUANTITY_PADDING + (hordaNro.quot - padding) * HORDA_TOTAL_HEIGHT;
    Button::draw(number, 0);

}

bool DisminuirTiempoHordaButton::belongsToHorda(int hordaId) {
    return horda == hordaId;
}
