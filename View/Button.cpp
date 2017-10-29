#include "Button.h"

Button::Button(int id, int posX, int posY, int width, int height,
               SDL_Texture *texture, MousePosition &mousePosition,
               Renderer &renderer) : id(id),
                                     mousePosition(mousePosition),
                                     button(SDL_Rect{posX, posY, width,
                                                     height}),
                                     renderer(renderer), texture(texture) {}

Button::~Button() = default;

void Button::draw() {
    if (this->isClicked()) {
        this->click();
        mousePosition.toggleActive();
    }
    renderer.copyEuclidean(texture, &button);
}

bool Button::isClicked() {
    return !(mousePosition.getPosX() < button.x ||
             mousePosition.getPosX() > (button.x + button.w) ||
             mousePosition.getPosY() < button.y ||
             mousePosition.getPosY() > (button.y + button.h)) &&
           mousePosition.isActive();
}