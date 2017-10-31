#include "UnitView.h"

#define WALKING_W_POS 1765
#define WALKING_H_POS 3537

#define WALKING_W 106
#define WALKING_H 119

#define WALKING_OFFSET_X 0
#define WALKING_OFFSET_Y 80

#define DYING_W 0
#define DYING_H 0

#define UNIT_WALKING_N 12
#define UNIT_DYING_N 18

UnitView::UnitView(int key, TextureLoader &textures, Renderer &renderer) :
        spriteWalking(textures.getTexture(key), renderer),
        spriteDying(textures.getTexture(key), renderer){
    spriteWalking.setSourceRect(WALKING_W_POS, WALKING_H_POS, WALKING_W, WALKING_H);
    spriteWalking.setDestRect(x, y, WALKING_W, WALKING_H);
    spriteWalking.setOffsetXY(WALKING_OFFSET_X, WALKING_OFFSET_Y);
}

void UnitView::setXY(int x, int y) {
    View::setXY(x, y);
    spriteWalking.setDestXY(x, y);
}

void UnitView::draw(Uint32 ticks) {
    spriteWalking.draw();

    Uint32 spriteN = (ticks / 150) % UNIT_WALKING_N;
    spriteWalking.setSourceXY(spriteN * WALKING_W + WALKING_W_POS,
                              WALKING_H_POS + 7 * WALKING_H);
    spriteWalking.draw();
}

void UnitView::move(int x, int y, int nextX, int nextY) {
    this->setXY(x, y);
}
