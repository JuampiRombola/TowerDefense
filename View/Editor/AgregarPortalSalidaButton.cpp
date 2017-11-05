#include "AgregarPortalSalidaButton.h"

AgregarPortalSalidaButton::AgregarPortalSalidaButton(int id,
                                                     SDL_Texture *texture,
                                                     MousePosition &mousePosition,
                                                     Renderer &renderer,
                                                     Editor &editor) : Button(
        id, 300, 100, 100, 100, texture, mousePosition, renderer),
                                                                       editor(editor) {}

void AgregarPortalSalidaButton::click() {
    editor.waitForExitPortalTile();
}