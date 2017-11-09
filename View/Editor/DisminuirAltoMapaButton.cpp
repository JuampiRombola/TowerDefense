#include "DisminuirAltoMapaButton.h"

DisminuirAltoMapaButton::DisminuirAltoMapaButton(SDL_Texture *texture,
                                                   MousePosition &mousePosition,
                                                   Renderer &renderer, Editor &editor)
        : Button(ALTO_RESTA_BUTTON_X, ALTO_RESTA_BUTTON_Y,
                 ALTO_RESTA_BUTTON_WIDTH, ALTO_RESTA_BUTTON_HEIGHT,
                 texture, mousePosition, renderer), editor(editor) {}

void DisminuirAltoMapaButton::click() {
    editor.disminuirAltoMapa();
}