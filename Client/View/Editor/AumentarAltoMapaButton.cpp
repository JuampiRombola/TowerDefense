#include "AumentarAltoMapaButton.h"

AumentarAltoMapaButton::AumentarAltoMapaButton(SDL_Texture *texture,
                                           MousePosition &mousePosition,
                                           Renderer &renderer, Editor &editor)
        : Button(ALTO_SUMA_BUTTON_X, ALTO_SUMA_BUTTON_Y, ALTO_SUMA_BUTTON_WIDTH, ALTO_SUMA_BUTTON_HEIGHT,
                 texture, mousePosition, renderer), editor(editor) {}

void AumentarAltoMapaButton::click() {
    editor.aumentarAltoMapa();
}