#include "DisminuirAnchoMapaButton.h"

DisminuirAnchoMapaButton::DisminuirAnchoMapaButton(SDL_Texture *texture,
                                                 MousePosition &mousePosition,
                                                 Renderer &renderer, Editor &editor)
        : Button(ANCHO_RESTA_BUTTON_X, ANCHO_RESTA_BUTTON_Y,
                 ANCHO_RESTA_BUTTON_WIDTH, ANCHO_RESTA_BUTTON_HEIGHT,
                 texture, mousePosition, renderer), editor(editor) {}

void DisminuirAnchoMapaButton::click() {
    editor.disminuirAnchoMapa();
}