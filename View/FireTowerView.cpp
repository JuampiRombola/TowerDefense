#include "FireTowerView.h"
#include "SpriteNamesConfig.h"

#define FTOWER_W 64
#define FTOWER_H 104
#define FTOWEROFFSET_X (-32)
#define FTOWEROFFSET_Y 92

#define FIRE_W 23
#define FIRE_H 45
#define FIREOFFSET_X (-64)
#define FIREOFFSET_Y 134

#define FTOWER_N 30

FireTowerView::FireTowerView(TextureLoader &textures, Renderer &renderer) :
        spriteTower(textures.getTexture(FIRE_TOWER), renderer),
        spriteFire(textures.getTexture(FIRE_TOWER), renderer) {

    spriteTower.setSourceRect(0, 0, FTOWER_W, FTOWER_H);
    spriteTower.setDestRect(x, y, FTOWER_W + FTOWER_W / 2,
                            FTOWER_H + FTOWER_H / 2);
    spriteTower.setOffsetXY(FTOWEROFFSET_X, FTOWEROFFSET_Y);

    spriteFire.setSourceRect(0, 0, FIRE_W, FIRE_H);
    spriteFire.setDestRect(x, y, FIRE_W + FIRE_W / 2,
                           FIRE_H + FIRE_H / 2);
    spriteFire.setOffsetXY(FIREOFFSET_X, FIREOFFSET_Y);
}

FireTowerView::~FireTowerView() {}

void FireTowerView::draw(Uint32 ticks) {
    Uint32 spriteN = (ticks / 100) % FTOWER_N;

    spriteFire.setSourceXY(spriteN * FTOWER_W, 0);
    spriteTower.draw();

    spriteFire.setSourceXY(spriteN * FIRE_W, FTOWER_H + 5);
    spriteFire.draw();
}

void FireTowerView::setXY(int x, int y) {
    View::setXY(x, y);
    spriteTower.setDestXY(x, y);
    spriteFire.setDestXY(x, y);
}