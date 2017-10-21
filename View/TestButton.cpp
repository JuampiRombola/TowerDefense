#include "TestButton.h"
#include <iostream>

TestButton::TestButton(int posX, int posY, int width, int height,
                       SDL_Texture *texture, MousePosition &mousePosition,
                       Renderer &renderer) : Button(posX, posY, width,
                       height, texture, mousePosition, renderer) {}

TestButton::~TestButton() = default;

void TestButton::click() {
    std::cout << "Estoy tocando el botón!\n";
}