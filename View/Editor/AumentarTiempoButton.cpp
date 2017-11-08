#include "AumentarTiempoButton.h"

AumentarTiempoButton::AumentarTiempoButton(int horda,
                                           SDL_Texture *texture,
                                           MousePosition &mousePosition,
                                           Renderer &renderer, Editor &editor)
        : Button(0, 0, HORDA_MODIFY_QUANTITY_SIZE, HORDA_MODIFY_QUANTITY_SIZE,
                 texture, mousePosition, renderer), horda(horda),
          editor(editor) {}

void AumentarTiempoButton::click() {
    editor.aumentarTiempoHorda(horda);
}

void AumentarTiempoButton::draw(int number) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    div_t enemigoNro = div(hordaNro.rem, HORDA_BUTTONS_PER_ENEMY);
    button.x = enemigoNro.quot * HORDA_ENEMIGO_IMG_SIZE +
               HORDA_MODIFY_QUANTITY_SIZE;
    button.y =
            HORDA_MODIFY_QUANTITY_PADDING + hordaNro.quot * HORDA_TOTAL_HEIGHT;
    Button::draw(number);

}

bool AumentarTiempoButton::belongsToHorda(int hordaId) {
    return horda == hordaId;
}
