#include "EliminarHordaButton.h"

#include <utility>
#include <stdlib.h>

EliminarHordaButton::EliminarHordaButton(int horda, SDL_Texture *texture,
                                         MousePosition &mousePosition,
                                         Renderer &renderer, Editor &editor,
                                         std::function<void(
                                                 int)> deleteButtonsFn)
        : Button(0, 0, 50, 50, texture, mousePosition, renderer),
          editor(editor), horda(horda), deleteButtonsFn(deleteButtonsFn) {}

void EliminarHordaButton::click() {
    editor.eliminarHorda(horda);
    deleteButtonsFn(horda);
}

void EliminarHordaButton::draw(int number, int padding) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    if (hordaNro.quot < padding)
        return;
    button.x = (HORDA_TOTAL_ENEMIES + 2) * HORDA_ENEMIGO_IMG_SIZE +
               HORDA_QUANTITY_WIDTH;
    button.y = HORDA_ENEMIGO_PADDING +
               (hordaNro.quot - padding) * HORDA_TOTAL_HEIGHT;
    Button::draw(number, 0);
}

bool EliminarHordaButton::belongsToHorda(int hordaNro) {
    return horda == hordaNro;
}
