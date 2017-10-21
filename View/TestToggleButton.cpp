#include "TestToggleButton.h"
#include <iostream>

TestToggleButton::TestToggleButton(int posX, int posY, int width, int height,
                       SDL_Texture *activeTexture, SDL_Texture *inactiveTexture,
                       MousePosition &mousePosition, Renderer &renderer) :
        ToggleButton(posX, posY, width, height, activeTexture, inactiveTexture,
                     mousePosition, renderer) {}

TestToggleButton::~TestToggleButton() = default;

void TestToggleButton::click() {
    std::cout << "Me cambian de estado!\n";
}