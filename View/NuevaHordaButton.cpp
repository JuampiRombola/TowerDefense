#include "NuevaHordaButton.h"

NuevaHordaButton::NuevaHordaButton(int id, SDL_Texture *texture,
                                   MousePosition &mousePosition,
                                   Renderer &renderer, Editor &editor) : Button(
        id, 0, 100, 200, 50, texture, mousePosition, renderer), editor
                                                                                 (editor) {}

void NuevaHordaButton::click() {
    editor.agregarHorda();
}

NuevaHordaButton::~NuevaHordaButton() = default;