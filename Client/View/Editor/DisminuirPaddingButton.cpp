#include "DisminuirPaddingButton.h"

DisminuirPaddingButton::DisminuirPaddingButton(unsigned int &padding,
                                               SDL_Texture *texture,
                                               MousePosition &mousePosition,
                                               Renderer &renderer) : Button(
        SCROLL_DOWN_BUTTON_X, SCROLL_DOWN_BUTTON_Y, SCROLL_DOWN_BUTTON_WIDTH,
        SCROLL_DOWN_BUTTON_HEIGHT, texture, mousePosition, renderer), padding
        (padding) {}

void DisminuirPaddingButton::click() {
    if (padding == 0)
        return;
    --padding;
}