#include "Button.h"

Button::Button(int posX, int posY, int width, int height,
               SDL_Texture *texture, MousePosition &mousePosition,
               Renderer &renderer) : mousePosition(mousePosition),
                                     Image(posX, posY, width, height, texture,
                                           renderer) {}

Button::~Button() = default;

void Button::draw(int number, int padding) {
    if (this->isClicked()) {
        this->click();
        mousePosition.deactivate();
    }
    Image::draw(number, 0);
}

bool Button::isClicked() {
    return !(mousePosition.getPosX() < button.x ||
             mousePosition.getPosX() > (button.x + button.w) ||
             mousePosition.getPosY() < button.y ||
             mousePosition.getPosY() > (button.y + button.h)) &&
           mousePosition.isActive();
}

bool Button::wasLastClick() {
    return !(mousePosition.getPosX() < button.x ||
             mousePosition.getPosX() > (button.x + button.w) ||
             mousePosition.getPosY() < button.y ||
             mousePosition.getPosY() > (button.y + button.h));
}

bool Button::isMarked() {
    return (this->wasLastClick() && mousePosition.isMarked());
}
