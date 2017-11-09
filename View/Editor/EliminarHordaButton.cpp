#include "EliminarHordaButton.h"

#include <utility>

EliminarHordaButton::EliminarHordaButton(int horda, SDL_Texture *texture,
                                         MousePosition &mousePosition,
                                         Renderer &renderer, Editor &editor,
                                         std::function<void(int)> deleteButtonsFn)
        : Button(0, 0, 50, 50, texture, mousePosition, renderer),
          editor(editor), horda(horda), deleteButtonsFn(deleteButtonsFn) {}

void EliminarHordaButton::click() {
    editor.eliminarHorda(horda);
    deleteButtonsFn(horda);
}

void EliminarHordaButton::draw(int number) {
    div_t hordaNro = div(number - TOTAL_MAIN_BUTTONS, HORDA_TOTAL_BUTTONS);
    button.x = (HORDA_TOTAL_ENEMIES + 1) * HORDA_ENEMIGO_IMG_SIZE;
    button.y = HORDA_ENEMIGO_PADDING + hordaNro.quot * HORDA_TOTAL_HEIGHT;
    Button::draw(number);
}

bool EliminarHordaButton::belongsToHorda(int hordaNro) {
    return horda == hordaNro;
}
