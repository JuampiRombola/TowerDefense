#include "AgregarTierraFirmeButton.h"

AgregarTierraFirmeButton::AgregarTierraFirmeButton(SDL_Texture *texture,
                                                   MousePosition &mousePosition,
                                                   Renderer &renderer,
                                                   Editor &editor)
        : Button(AGREGAR_TIERRA_BUTTON_X, AGREGAR_TIERRA_BUTTON_Y,
                 AGREGAR_TIERRA_BUTTON_WIDTH, AGREGAR_TIERRA_BUTTON_HEIGHT,
                 texture,
                 mousePosition, renderer),
          editor(editor) {}

void AgregarTierraFirmeButton::click() {
    editor.waitForStructureTile();
}