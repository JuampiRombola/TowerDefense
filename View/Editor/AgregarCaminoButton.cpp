#include "AgregarCaminoButton.h"

AgregarCaminoButton::AgregarCaminoButton(int id, SDL_Texture *texture,
                                         MousePosition &mousePosition,
                                         Renderer &renderer, Editor &editor)
        : Button(id, 0, 500, 100, 100, texture, mousePosition, renderer),
          editor(editor) {}

void AgregarCaminoButton::click() {
    editor.waitForPathTile();
}