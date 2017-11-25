#include "WaitActionButton.h"
#include "../Common/SpriteNamesConfig.h"
#include "ViewConstants.h"

#define BUTTON_OFFSET 200
#define FONT_SIZE_KEY 13
#define ADJUST_X 13
#define ADJUST_Y 15

WaitActionButton::WaitActionButton(Renderer &r, TextureLoader &tl,
                             int spriteKey, MousePosition &mousePosition,
                             int x, int y, int w, int h, int &cmd,
                             std::string &s) :
        GameButton(r, tl, spriteKey, mousePosition, x, y, w, h, cmd),
        t(SDL_GetTicks()), keySym(nullptr) {
    this->mapKey(spriteKey);

    keySym = new Announcement(s, renderer, FONT_SIZE_KEY);
    keySym->setDestXY(button.x + button.w - ADJUST_X,
                      button.y + button.h - ADJUST_Y);
}

WaitActionButton::~WaitActionButton() {
    if (keySym) delete keySym;
}

void WaitActionButton::draw() {
    Uint32 currentTime = SDL_GetTicks();
    bar.addPart(currentTime - t);
    t = currentTime;
    background.draw(0, 0);
    bar.draw();
    Button::draw(0, 0);
    if ((cmd != key) && bar.isFull())
        edge.draw(0, 0);
    keySym->draw();
}

void WaitActionButton::mapKey(int spriteKey) {
    key = spriteKey - BUTTON_OFFSET;
}
