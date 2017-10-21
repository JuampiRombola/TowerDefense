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
    Button* testButton = new TestButton(0, 0, 200, 200, texture,
                                        mousePosition, renderer);
    buttons.push_back(testButton);
}