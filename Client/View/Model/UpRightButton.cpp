#include "UpRightButton.h"
#include "ViewConstants.h"

#define FONT_SIZE_BUTTON_UP 9
#define ADJUST_X_BUTTON_UP 2
#define ADJUST_Y_BUTTON_UP 11
#define KEY_SIZE 6

UpRightButton::UpRightButton(Window &w, int type, int &cmd,
                         SDL_Texture *texture,
                         SDL_Texture *transp,
                         MousePosition &mousePosition,
                         Renderer &renderer, int n, std::string &text)
        : type(type), command(cmd),
          Button(w.getWidth() - n*EXIT_BUTTON_SIZE - n*PADDING_HUD,
                 PADDING_HUD, EXIT_BUTTON_SIZE, EXIT_BUTTON_SIZE,
                 texture, mousePosition, renderer),
          transparency(button.x, button.y, button.w, button.h,
                       transp, renderer) {
    keySym = new Announcement(text, renderer, FONT_SIZE_BUTTON_UP);
    keySym->setDestXY(static_cast<int>(button.x + button.w
                      - ADJUST_X_BUTTON_UP - text.size() * KEY_SIZE),
                      button.y + button.h - ADJUST_Y_BUTTON_UP);
}

void UpRightButton::draw(int number, int padding) {
    Button::draw(0, 0);
    if ((command != type) && !this->wasLastClick())
        transparency.draw(0, 0);
    keySym->draw();
}

void UpRightButton::click() {
    command = type;
}