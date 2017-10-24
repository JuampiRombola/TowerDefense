#include "NuevaHordaButton.h"


NuevaHordaButton::NuevaHordaButton(SDL_Texture *texture, MousePosition &mousePosition,
                                   Renderer& renderer, Editor &editor) :
        Button(0, 100, 200, 50, texture, mousePosition, renderer), editor
        (editor) {}

void NuevaHordaButton::click() {
    editor.agregarHorda();
}

NuevaHordaButton::~NuevaHordaButton() = default;