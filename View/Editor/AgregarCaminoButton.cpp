#include "AgregarCaminoButton.h"

AgregarCaminoButton::AgregarCaminoButton(SDL_Texture *texture,
                                         MousePosition &mousePosition,
                                         Renderer &renderer,
                                         Editor &editor)
        : Button(AGREGAR_CAMINO_BUTTON_X, AGREGAR_CAMINO_BUTTON_Y,
                 AGREGAR_CAMINO_BUTTON_WIDTH, AGREGAR_CAMINO_BUTTON_HEIGHT,
                 texture, mousePosition, renderer), editor(editor) {}

void AgregarCaminoButton::click() {
    editor.waitForPathTile();
}