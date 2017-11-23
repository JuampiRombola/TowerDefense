#include "InstantButton.h"
#include "../Common/SpriteNamesConfig.h"
#include "ViewConstants.h"

InstantButton::InstantButton(Renderer &r, TextureLoader &tl,
                             int spriteKey, MousePosition &mousePosition,
                             int x, int y, int w, int h, int &cmd) :
        GameButton(r, tl, spriteKey, mousePosition, x, y, w, h, cmd) {
    this->mapKey(spriteKey);
}

void InstantButton::draw() {
    background.draw(0, 0);
    bar.draw();
    Button::draw(0, 0);
    if (!this->isMarked() && bar.isFull())
        edge.draw(0, 0);
}

void InstantButton::click() {
    GameButton::click();
}

void InstantButton::mapKey(int spriteKey) {
    if (spriteKey == DAMAGE)
        key = CMD_DAMAGE;
    if (spriteKey == RANGE)
        key = CMD_RANGE;
    if (spriteKey == IMPACT)
        key = CMD_IMPACT;
    if (spriteKey == FREEZE)
        key = CMD_FREEZE;
}
