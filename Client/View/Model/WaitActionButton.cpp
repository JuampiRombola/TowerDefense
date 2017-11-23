#include "WaitActionButton.h"
#include "../Common/SpriteNamesConfig.h"
#include "ViewConstants.h"

#define BUTTON_OFFSET 200

WaitActionButton::WaitActionButton(Renderer &r, TextureLoader &tl,
                             int spriteKey, MousePosition &mousePosition,
                             int x, int y, int w, int h, int &cmd) :
        GameButton(r, tl, spriteKey, mousePosition, x, y, w, h, cmd) {
    this->mapKey(spriteKey);
}

void WaitActionButton::draw() {
    background.draw(0, 0);
    bar.draw();
    Button::draw(0, 0);
    if (!this->wasLastClick() && bar.isFull())
        edge.draw(0, 0);
}

void WaitActionButton::mapKey(int spriteKey) {
    key = spriteKey - BUTTON_OFFSET;
}
