#include "AumentarPaddingButton.h"

AumentarPaddingButton::AumentarPaddingButton(unsigned int &padding, SDL_Texture
*texture,
                                             MousePosition &mousePosition,
                                             Renderer &renderer) : Button(
        SCROLL_UP_BUTTON_X, SCROLL_UP_BUTTON_Y, SCROLL_UP_BUTTON_WIDTH,
        SCROLL_UP_BUTTON_HEIGHT, texture, mousePosition, renderer),
                                                                   padding(padding) {}

void AumentarPaddingButton::click() {
    ++padding;
}