#include "Button.h"

Button::Button(int posX, int posY, int width, int height, SDL_Texture *texture,
                MousePosition &mousePosition, Renderer& renderer) :
                button({posX, posY, width, height}), mousePosition
                (mousePosition), renderer(renderer), texture(texture) {}

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
            mousePosition.getPosY() > (button.y + button.h))
            &&
            mousePosition.isActive();
}