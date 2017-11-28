#include "AumentarPaddingButton.h"

AumentarPaddingButton::AumentarPaddingButton(unsigned int &padding, SDL_Texture *texture,
                                             MousePosition &mousePosition, Renderer &renderer)
        : Button(SCROLL_UP_BUTTON_X, renderer.getWindowHeight()
                 - SCROLL_UP_BUTTON_Y, SCROLL_BUTTON_SIZE, SCROLL_BUTTON_SIZE,
                 texture, mousePosition, renderer), padding(padding) {}

void AumentarPaddingButton::click() {
    ++padding;
}