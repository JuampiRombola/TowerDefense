#include "UpRightButton.h"
#include "ViewConstants.h"

UpRightButton::UpRightButton(Window &w, int type, int &cmd,
                         SDL_Texture *texture,
                         SDL_Texture *transp,
                         MousePosition &mousePosition,
                         Renderer &renderer, int n)
        : type(type), command(cmd),
          Button(w.getWidth() - n*EXIT_BUTTON_SIZE - n*PADDING_HUD,
                 PADDING_HUD, EXIT_BUTTON_SIZE, EXIT_BUTTON_SIZE,
                 texture, mousePosition, renderer),
          transparency(button.x, button.y, button.w, button.h,
                       transp, renderer) {}

void UpRightButton::draw(int number, int padding) {
    Button::draw(0, 0);
    if (!this->wasLastClick())
        transparency.draw(0, 0);
}

void UpRightButton::click() {
    command = type;
}