#include "Buttons.h"

Buttons::Buttons(MousePosition &mousePosition, Renderer &renderer) :
        mousePosition(mousePosition), renderer(renderer) {}

Buttons::~Buttons() {
    for (Button* button : buttons) {
        delete button;
    }
}

void Buttons::draw() {
    for (Button* button : buttons) {
        button->draw();
    }
}

void Buttons::addTestButton(SDL_Texture* texture) {
    Button* testButton = new TestButton(0, 0, 100, 100, texture,
                                        mousePosition, renderer);
    buttons.push_back(testButton);
}

void Buttons::addTestToggleButton(SDL_Texture *activeTexture,
                                  SDL_Texture *inactiveTexture) {
    Button* testToggleButton = new TestToggleButton(100, 0, 100, 100,
                                                    activeTexture,
                                                    inactiveTexture,
                                                    mousePosition, renderer);
    buttons.push_back(testToggleButton);
}