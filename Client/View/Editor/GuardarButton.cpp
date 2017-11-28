#include <stdlib.h>
#include "GuardarButton.h"

GuardarButton::GuardarButton(SDL_Texture *texture, MousePosition &mousePosition,
                             Renderer &renderer, Editor &editor) :
        Button(renderer.getWindowWidth() - SAVE_BUTTON_X,
               SAVE_BUTTON_Y, SAVE_BUTTON_WIDTH, SAVE_BUTTON_HEIGHT,
               texture, mousePosition, renderer), editor(editor) {}

void GuardarButton::click() {
    editor.exportar();
}
