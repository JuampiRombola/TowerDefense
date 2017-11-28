#include "NuevaHordaButton.h"

NuevaHordaButton::NuevaHordaButton(unsigned int &padding, SDL_Texture *texture,
                                   MousePosition &mousePosition,
                                   Renderer &renderer, Editor &editor,
                                   std::function<void(int)> addButtonsFn)
        : Button(NUEVA_HORDA_BUTTON_X, renderer.getWindowHeight()
          - NUEVA_HORDA_BUTTON_Y, NUEVA_HORDA_BUTTON_WIDTH,
          NUEVA_HORDA_BUTTON_HEIGHT, texture, mousePosition, renderer),
          idHorda(0), editor(editor), addButtonsFn(std::move(addButtonsFn)),
          padding(padding) {}

void NuevaHordaButton::click() {
    editor.agregarHorda(++idHorda);
    addButtonsFn(idHorda);
    padding = MAX_PADDING;
}

