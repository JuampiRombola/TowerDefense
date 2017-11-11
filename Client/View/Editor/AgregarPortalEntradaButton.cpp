#include "AgregarPortalEntradaButton.h"

AgregarPortalEntradaButton::AgregarPortalEntradaButton(SDL_Texture *texture,
                                                       MousePosition &mousePosition,
                                                       Renderer &renderer,
                                                       Editor &editor) :
        Button(AGREGAR_PORTAL_ENTRADA_BUTTON_X, AGREGAR_PORTAL_ENTRADA_BUTTON_Y,
               AGREGAR_PORTAL_ENTRADA_BUTTON_WIDTH,
               AGREGAR_PORTAL_ENTRADA_BUTTON_HEIGHT, texture, mousePosition,
               renderer), editor(editor) {}

void AgregarPortalEntradaButton::click() {
    editor.waitForSpawnPortalTile();
}