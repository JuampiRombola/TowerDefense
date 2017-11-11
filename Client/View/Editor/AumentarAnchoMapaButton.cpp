#include "AumentarAnchoMapaButton.h"

AumentarAnchoMapaButton::AumentarAnchoMapaButton(SDL_Texture *texture,
                                               MousePosition &mousePosition,
                                               Renderer &renderer, Editor &editor)
        : Button(ANCHO_SUMA_BUTTON_X, ANCHO_SUMA_BUTTON_Y, ANCHO_SUMA_BUTTON_WIDTH, ANCHO_SUMA_BUTTON_HEIGHT,
                 texture, mousePosition, renderer), editor(editor) {}

void AumentarAnchoMapaButton::click() {
    editor.aumentarAnchoMapa();
}