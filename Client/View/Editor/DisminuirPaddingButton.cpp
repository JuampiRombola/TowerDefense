#include "DisminuirPaddingButton.h"

DisminuirPaddingButton::DisminuirPaddingButton(unsigned int &padding, SDL_Texture *texture,
                                               MousePosition &mousePosition, Renderer &renderer)
        : Button(SCROLL_DOWN_BUTTON_X, renderer.getWindowHeight()
          - SCROLL_BUTTON_SIZE, SCROLL_BUTTON_SIZE, SCROLL_BUTTON_SIZE,
                 texture, mousePosition, renderer), padding(padding) {}

void DisminuirPaddingButton::click() {
    if (padding == 0)
        return;
    --padding;
}