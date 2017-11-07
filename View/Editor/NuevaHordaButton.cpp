#include "NuevaHordaButton.h"

NuevaHordaButton::NuevaHordaButton(SDL_Texture *texture, MousePosition &mousePosition,
                                   Renderer &renderer, Editor &editor,
                                   std::function<void(int)> addButtonsFn)
        : Button(
        NUEVA_HORDA_BUTTON_X, NUEVA_HORDA_BUTTON_Y, NUEVA_HORDA_BUTTON_WIDTH,
        NUEVA_HORDA_BUTTON_HEIGHT, texture, mousePosition, renderer),
          idHorda(0), editor(editor), addButtonsFn(addButtonsFn){}

void NuevaHordaButton::click() {
    editor.agregarHorda(++idHorda);
    addButtonsFn(idHorda);
}

