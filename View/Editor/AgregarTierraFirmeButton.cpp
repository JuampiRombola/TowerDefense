#include "AgregarTierraFirmeButton.h"

AgregarTierraFirmeButton::AgregarTierraFirmeButton(int id, SDL_Texture *texture,
                                         MousePosition &mousePosition,
                                         Renderer &renderer, Editor &editor)
        : Button(id, 100, 100, 100, 100, texture, mousePosition, renderer),
          editor(editor) {}

void AgregarTierraFirmeButton::click() {
    editor.waitForStructureTile();
}