#include "AgregarPortalSalidaButton.h"

AgregarPortalSalidaButton::AgregarPortalSalidaButton(SDL_Texture *texture,
                                                     MousePosition &mousePosition,
                                                     Renderer &renderer, Editor &editor) : Button(
        AGREGAR_PORTAL_SALIDA_BUTTON_X, AGREGAR_PORTAL_SALIDA_BUTTON_Y,
        AGREGAR_PORTAL_SALIDA_BUTTON_WIDTH, AGREGAR_PORTAL_SALIDA_BUTTON_HEIGHT, texture,
        mousePosition, renderer), editor(editor) {}

void AgregarPortalSalidaButton::click() {
    editor.waitForExitPortalTile();
}