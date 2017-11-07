#include "AgregarPortalEntradaButton.h"

AgregarPortalEntradaButton::AgregarPortalEntradaButton(int id,
                                                       SDL_Texture *texture,
                                                       MousePosition &mousePosition,
                                                       Renderer &renderer,
                                                       Editor &editor) : Button(
        id, 200, 100, 100, 100, texture, mousePosition, renderer), editor
        (editor) {}

void AgregarPortalEntradaButton::click() {
    editor.waitForSpawnPortalTile();
}