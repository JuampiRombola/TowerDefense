#include "SalidaButton.h"

SalidaButton::SalidaButton(SDL_Texture *texture, MousePosition &mousePosition,
                             Renderer &renderer, Editor &editor) :
        Button(renderer.getWindowWidth() - EXIT_BUTTON_X,
               SAVE_BUTTON_Y, SAVE_BUTTON_WIDTH, SAVE_BUTTON_HEIGHT,
               texture, mousePosition, renderer), editor(editor) {}

void SalidaButton::click() {
    editor.activateExit();
}
