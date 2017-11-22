#include "PadlockButton.h"
#include "../Common/SpriteNamesConfig.h"


PadlockButton::PadlockButton(Renderer &r, TextureLoader &tl,
                             MousePosition &mousePosition,
                             int x, int y, int w, int h) :
        GameButton(r, tl, CANDADO_ICON, mousePosition, x, y, w, h, x) {}

void PadlockButton::draw() {
    background.draw(0, 0);
    Image::draw(0, 0);
}

void PadlockButton::click() {}
