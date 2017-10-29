#include "ToggleButton.h"

ToggleButton::ToggleButton(int id, int posX, int posY, int width, int height,
                           SDL_Texture *activeTexture,
                           SDL_Texture *inactiveTexture,
                           MousePosition &mousePosition, Renderer &renderer)
        : Button(id, posX, posY, width, height, inactiveTexture, mousePosition,
                 renderer), activeTexture(activeTexture),
          inactiveTexture(inactiveTexture) {}

ToggleButton::~ToggleButton() = default;

void ToggleButton::toggleTexture() {
    if (texture == inactiveTexture)
        texture = activeTexture;
    else
        texture = inactiveTexture;
}

void ToggleButton::draw() {
    if (this->isClicked())
        this->toggleTexture();
    Button::draw();
}
