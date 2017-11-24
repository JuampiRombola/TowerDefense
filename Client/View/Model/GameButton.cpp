#include "GameButton.h"
#include "../Common/SpriteNamesConfig.h"

#define EDGE_X 7
#define EDGE_Y 19

#define BACKGROUND_H 26

#define SRC_BAR_W 65
#define SRC_BAR_H 9
#define BAR_X 3
#define BAR_Y 3
#define BAR_W 4

GameButton::GameButton(Renderer &r, TextureLoader &tl,
                       int spriteKey, MousePosition &mousePosition,
                       int x, int y, int w, int h, int &cmd) :
        Button(x + EDGE_X, y + EDGE_Y,
               w, h, tl.getTexture(spriteKey), mousePosition, r),
        edge(x + EDGE_X, y + EDGE_Y, w, h,
             tl.getTexture(BUTTON_EDGE), r),
        background(x, y, w + 2*EDGE_X, h + BACKGROUND_H,
                   tl.getTexture(BUTTON_BG), r),
        bar(r, tl.getTexture(BUTTON_BAR), SRC_BAR_W, SRC_BAR_H,
            w + 2*BAR_W, SRC_BAR_H), cmd(cmd) {
    bar.setDestXY(x + BAR_X, y + BAR_Y);
    bar.setPart(1);
}

void GameButton::draw() {
    background.draw(0, 0);
    bar.draw();
    Button::draw(0, 0);
    edge.draw(0, 0);
}

void GameButton::click() {
    if (bar.isFull())
        cmd = key;
}

void GameButton::setTotalProgressBar(Uint32 t) {
    bar.setTotal(t);
}

void GameButton::setPartProgressBar(Uint32 p) {
    bar.setPart(p);
}

int GameButton::getKey() {
    return key;
}

void GameButton::addPartProgressBar(Uint32 p) {
    bar.addPart(p);
}

bool GameButton::isFullProgressBar() {
    return bar.isFull();
}
